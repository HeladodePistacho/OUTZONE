#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "ENEMY_Basic_Robot.h"
#include "ENEMY_Tiny_Turret.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	sprites = App->textures->Load("enemy_basic_sprites_all.png");
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].y * (-SCREEN_SIZE) < App->render->camera.y + (App->render->camera.h * SCREEN_SIZE) + SPAWN_MARGIN)
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
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
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
			enemies[i] = new ENEMY_Basic_Robot(info.x, info.y);
			break;
		case ENEMY_TYPES::TINY_TURRET:
			enemies[i] = new ENEMY_Tiny_Turret(info.x, info.y);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_PLAYER_SHOT)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				App->particles->AddParticle(App->particles->basic_enemy_explosion, App->enemies->enemies[i]->position.x, App->enemies->enemies[i]->position.y, COLLIDER_NONE, UNDEFINED);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}