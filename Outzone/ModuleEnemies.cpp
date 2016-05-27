#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "ENEMY_Basic_Robot.h"
#include "ENEMY_Tiny_Turret.h"
#include "ENEMY_Big_Turret_Left.h"
#include "ENEMY_Big_Turret_Right.h"
#include "ENEMY_Golden_Turret.h"
#include "ENEMY_Car.h"
#include "ENEMY_Red_Robot.h"
#include "ENEMY_Blue_Robot.h"
#include "ENEMY_Beatle.h"
#include "ModuleObjects.h"
#include "OBJECT_Upgrade.h"
#include "ModulePlayer.h"
#include "ModuleInterfice.h"
#define SPAWN_MARGIN 150

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies[i] = nullptr;
		
	}
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{}

bool ModuleEnemies::Start()
{
	sprites = App->textures->Load("enemies_sprites.png");
	
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].y * (-SCREEN_SIZE) < App->render->camera.y + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	if (enemies[i] != nullptr) enemies[i]->Attack();


	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if ((enemies[i]->position.y * -2) < (App->render->camera.y - (App->render->camera.h * 2)))
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		
		queue[i].type = NO_TYPE;

	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, MOVEMENT_TYPES m_type)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].movement_type = m_type;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BASIC_ROBOT:
			enemies[i] = new ENEMY_Basic_Robot(info.x, info.y, info.movement_type);
			break;
		case ENEMY_TYPES::TINY_TURRET:
			enemies[i] = new ENEMY_Tiny_Turret(info.x, info.y);
			break;
		case ENEMY_TYPES::CAR:
			enemies[i] = new ENEMY_Car(info.x, info.y);
			break;
		case ENEMY_TYPES::BIG_TURRET_LEFT:
			enemies[i] = new ENEMY_Big_Turret_Left(info.x, info.y);
			break;
		case ENEMY_TYPES::BIG_TURRET_RIGHT:
			enemies[i] = new ENEMY_Big_Turret_Right(info.x, info.y);
			break;
		case ENEMY_TYPES::GOLDEN_TURRET:
			enemies[i] = new ENEMY_Golden_Turret(info.x, info.y);
			break;
		case ENEMY_TYPES::RED_ROBOT:
			enemies[i] = new ENEMY_Red_Robot(info.x, info.y, info.movement_type);
			break;
		case ENEMY_TYPES::BEATLE:
			enemies[i] = new ENEMY_Beatle(info.x, info.y, info.movement_type);
			break;
		case ENEMY_TYPES::BLUE_ROBOT:
			enemies[i] = new ENEMY_Blue_Robot(info.x, info.y, info.movement_type);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (c1->type == COLLIDER_SHIELD && c2->type == COLLIDER_PLAYER_SHOT ){
				App->particles->AddParticle(App->particles->car_hole, App->enemies->enemies[i]->position.x - 5, App->enemies->enemies[i]->position.y, COLLIDER_NONE, UNDEFINED);
				App->particles->AddParticle(App->particles->big_enemy_explosion, App->enemies->enemies[i]->position.x - 30, App->enemies->enemies[i]->position.y - 5, COLLIDER_NONE, UNDEFINED);
				App->interfice->score += 20;
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
			else if (c1->type == COLLIDER_SHIELD && c2->type == COLLIDER_PLAYER && (c1->rect.y - 2 + c1->rect.h > c2->rect.y)){
				App->particles->AddParticle(App->particles->car_hole, App->enemies->enemies[i]->position.x - 5, App->enemies->enemies[i]->position.y, COLLIDER_NONE, UNDEFINED);
				App->particles->AddParticle(App->particles->big_enemy_explosion, App->enemies->enemies[i]->position.x - 30, App->enemies->enemies[i]->position.y - 5, COLLIDER_NONE, UNDEFINED);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
			else if (c1->type == COLLIDER_ENEMY && (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_PLAYER_SHOT))
			{
				if (enemies[i]->enemy_type == BIG_TURRET_LEFT ||enemies[i]->enemy_type == BIG_TURRET_RIGHT)
				{
					App->particles->AddParticle(App->particles->big_enemy_explosion, App->enemies->enemies[i]->position.x-40, App->enemies->enemies[i]->position.y -40, COLLIDER_NONE, UNDEFINED);
					App->particles->AddParticle(App->particles->big_turret_fire, App->enemies->enemies[i]->position.x , App->enemies->enemies[i]->position.y, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 810;
				}
				else if (enemies[i]->enemy_type == GOLDEN_TURRET)
				{
					App->particles->AddParticle(App->particles->basic_enemy_explosion, App->enemies->enemies[i]->position.x -10, App->enemies->enemies[i]->position.y -2, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 290;
				}
				else if (enemies[i]->enemy_type == TINY_TURRET)
				{
					App->particles->AddParticle(App->particles->basic_enemy_explosion, App->enemies->enemies[i]->position.x - 10, App->enemies->enemies[i]->position.y, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 410;
				}
				else if (enemies[i]->enemy_type == BASIC_ROBOT)
				{
					App->particles->AddParticle(App->particles->basic_enemy_explosion, App->enemies->enemies[i]->position.x, App->enemies->enemies[i]->position.y, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 390;
				}
				else if (enemies[i]->enemy_type == RED_ROBOT)
				{
					App->particles->AddParticle(App->particles->basic_enemy_explosion, App->enemies->enemies[i]->position.x - 7, App->enemies->enemies[i]->position.y - 5, COLLIDER_NONE, UNDEFINED);
					App->interfice->score += 390;

					if (App->player->shotgun_lvl != 3)
					{
						App->objects->AddObject(OBJECT_TYPES::UPGRADE, App->enemies->enemies[i]->position.x + 7, App->enemies->enemies[i]->position.y + 10);
					}
					else App->objects->AddObject(OBJECT_TYPES::BOMB, App->enemies->enemies[i]->position.x + 7, App->enemies->enemies[i]->position.y + 10);
				}
				

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}