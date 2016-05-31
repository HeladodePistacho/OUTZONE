#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleObjects.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Object.h"
#include "OBJECT_Change_Box.h"
#include "OBJECT_Energy_Box.h"
#include "OBJECT_Upgrade.h"
#include "OBJECT_Car_Rail.h"
#include "OBJECT_Bomb.h"
#include "OBJECT_Car_Hole.h"
#include "ModulePlayer.h"
#include "ModuleInterfice.h"
#include "ModuleAudio.h"

#define SPAWN_MARGIN 50

ModuleObjects::ModuleObjects()
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
		objects[i] = nullptr;
}

// Destructor
ModuleObjects::~ModuleObjects()
{
}

bool ModuleObjects::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Game/objects_sprites.png");
	Power_up = App->audio->Load_chunk("Game/power_up_weapon.wav");
	Energy_fx = App->audio->Load_chunk("Game/Energy.wav");

	return true;
}

update_status ModuleObjects::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (queue[i].type != OBJECT_TYPES::UNKNOWN)
		{
			if (queue[i].y * (-SCREEN_SIZE) < App->render->camera.y + (App->render->camera.h * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnObject(queue[i]);
				queue[i].type = OBJECT_TYPES::UNKNOWN;
				LOG("Spawning object at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleObjects::Update()
{

	for (uint i = 0; i < MAX_OBJECTS; ++i){
		if (objects[i] != nullptr) objects[i]->Draw(sprites);
		
	}
	return UPDATE_CONTINUE;
}

update_status ModuleObjects::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			if ((objects[i]->position.y * -2) < (App->render->camera.y - (App->render->camera.h * 2)))
			{
				LOG("DeSpawning object at %d", objects[i]->position.x * SCREEN_SIZE);
				delete objects[i];
				objects[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleObjects::CleanUp()
{
	LOG("Freeing all objects");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			delete objects[i];
			objects[i] = nullptr;
		}

		queue[i].type = UNKNOWN;
	}

	return true;
}

bool ModuleObjects::AddObject(OBJECT_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (queue[i].type == OBJECT_TYPES::UNKNOWN)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleObjects::SpawnObject(const ObjectInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; objects[i] != nullptr && i < MAX_OBJECTS; ++i);

	if (i != MAX_OBJECTS)
	{
		switch (info.type)
		{
		case OBJECT_TYPES::CHANGE_BOX:
			objects[i] = new Change_Box(info.x, info.y);
			break;

		case OBJECT_TYPES::ENERGY_BOX:
			objects[i] = new Energy_Box(info.x, info.y);
			break;
		
		case OBJECT_TYPES::UPGRADE:
			objects[i] = new Upgrade(info.x, info.y);
			break;
		case OBJECT_TYPES::BOMB:
			objects[i] = new Bomb(info.x, info.y);
			break;

		case OBJECT_TYPES::CAR_HOLE:
			objects[i] = new Car_Hole(info.x, info.y);
			break;

		case OBJECT_TYPES::CAR_RAIL:
			objects[i] = new Car_Rail(info.x, info.y);
			break;
		}
	}
}

void ModuleObjects::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr && objects[i]->GetCollider() == c1)
		{
			if (c2->type == COLLIDER_PLAYER_SHOT && c1->type == COLLIDER_CHEST)
			{
				if (objects[i]->type == CHANGE_BOX){
					App->particles->AddParticle(App->particles->basic_enemy_explosion, App->objects->objects[i]->position.x - 8, App->objects->objects[i]->position.y - 10, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 100;
					objects[i]->Update();
					break;
				}
				else if (objects[i]->type == ENERGY_BOX){
					App->particles->AddParticle(App->particles->basic_enemy_explosion, App->objects->objects[i]->position.x - 6, App->objects->objects[i]->position.y - 10, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 230;
					objects[i]->Update();
					break;
				}
			}
			else if (c2->type == COLLIDER_PLAYER && c1->type == COLLIDER_OBJECT){
				
				//Change box
				if (objects[i]->type == CHANGE_BOX){
					if (App->player->shotgun == false){
						App->player->shotgun = true;
					}
					else {
						App->player->shotgun = false;
						
					}
					Mix_PlayChannel(-1, Power_up, 0);
					App->interfice->score += 100;
				}

				//Energy box
				else if (objects[i]->type == ENERGY_BOX)
				{
					for (int k = 0; k < 15; k++){
						if (App->interfice->energy < App->interfice->energy_limit){
							App->interfice->energy++;
						}
					}
					Mix_PlayChannel(-1, Energy_fx, 0);
				}

				//Powerup
				else if (objects[i]->type == UPGRADE)
				{
					if (App->player->shotgun && App->player->shotgun_lvl < 3){
						App->player->shotgun_lvl++;
					}
					else if (App->player->shotgun_lvl < 3){
						App->player->shotgun_lvl++;
					}
					App->interfice->score += 100;
					Mix_PlayChannel(-1, Power_up, 0);
				}
				//Bomb
				else if (objects[i]->type == BOMB)
				{
					if (App->interfice->bombs_limit != App->interfice->bombs)
					{
						App->interfice->bombs++;
					}
				}


				delete objects[i];
				objects[i] = nullptr;
			}
		}
	}
}