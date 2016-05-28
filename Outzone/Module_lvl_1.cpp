#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_lvl_1.h"
#include "ModuleChangeScene.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleObjects.h"
#include "ModuleInterfice.h"
#include "ModuleVolumes.h"
#include "Module_Welcome.h"
#include "ModuleFonts.h"
Module_lvl_1::Module_lvl_1()
{
	// Level 1 
	background.x = 0;
	background.y = 0;
	background.w = 240;
	background.h = 3900;

}

Module_lvl_1::~Module_lvl_1()
{}




bool Module_lvl_1::Start()
{
	
	LOG("Loading lvl 1 stage");
		//Load Background
		graphics = App->textures->Load("level1.png");
		//Enable Particles
		App->particles->Enable();
		//Init Audio
		audio_lvl_1 = App->audio->Load("1st_Level_Theme.ogg");
		Mix_FadeInMusicPos(audio_lvl_1, 1, 2000, 1);
		Mix_PlayMusic(audio_lvl_1, -1);

		App->interfice->Enable();
		App->player->Enable();
		App->collision->Enable();
		App->enemies->Enable();
		App->objects->Enable();
		App->player->Reset();
		App->volumes->Enable();
		App->fonts->Enable();
		//COLLIDERS
		//WALLS
		App->collision->AddCollider({ 0, -152, 95, 195}, COLLIDER_WALL);//blue ship left
		App->collision->AddCollider({ 0, -162, 48, 50 }, COLLIDER_WALL);//blue ship left
		App->collision->AddCollider({ 178, -132, 59, 120 }, COLLIDER_WALL);//blue ship right
		App->collision->AddCollider({ 230, -12, 10, 20 }, COLLIDER_WALL);//blue ship right
		App->collision->AddCollider({ 200, -21, 42, 12 }, COLLIDER_WALL);//blue ship right
		App->collision->AddCollider({ 160, -1074, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, -914, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 191, -786, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 128, -722, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 63, -1747, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 193, -1779, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, -1811, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 96, -1908, 32, 62 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, -1340, 30, 168}, COLLIDER_WALL_FLAT);//turret wall
		App->collision->AddCollider({ 0, -1350, 107, 120 }, COLLIDER_WALL_FLAT);//turret wall
		App->collision->AddCollider({ 0, -1338, 123, 130 }, COLLIDER_WALL_FLAT);
		App->collision->AddCollider({ 200, -1354, 40, 142 }, COLLIDER_WALL_FLAT);//turret wall
		App->collision->AddCollider({ 0, -1640, 39, 140 }, COLLIDER_WALL_FLAT);//turret wall 2(pipiru)
		App->collision->AddCollider({ 0, -1626, 57, 130 }, COLLIDER_WALL_FLAT);
		App->collision->AddCollider({ 134, -1642, 103, 144 }, COLLIDER_WALL_FLAT);//turret wall 2
		App->collision->AddCollider({ 0, -3128, 29, 81 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 29, -3116, 46, 61 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 184, -3116, 46, 61 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 230, -3128, 14, 78 }, COLLIDER_WALL);//boss wall
	
		//ENEMIES
		//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 150, -50, MOVEMENT_TYPES::TYPE_DOWN_RIGHT);
		//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 95, -105, MOVEMENT_TYPES::TYPE_DOWN_RIGHT);
		//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 140, -140, MOVEMENT_TYPES::TYPE_DOWN_RIGHT);
		//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 105, -160, MOVEMENT_TYPES::TYPE_DOWN);
		//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 97, -205, MOVEMENT_TYPES::TYPE_DOWN);
		//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 130, -220, MOVEMENT_TYPES::TYPE_DOWN);
		
	
		//OBJECTS
		//Energy
		App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 195, -510);
		App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 80, -1195);
		App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 135, -1880);
		App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 4, -2930);
		App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 7, -3208);
		//Change
		App->objects->AddObject(OBJECT_TYPES::CHANGE_BOX, 200, -465);
		App->objects->AddObject(OBJECT_TYPES::CHANGE_BOX, 0, -975);
		App->objects->AddObject(OBJECT_TYPES::CHANGE_BOX, 0, -1485);
		App->objects->AddObject(OBJECT_TYPES::CHANGE_BOX, 200, -2095);
		App->objects->AddObject(OBJECT_TYPES::CHANGE_BOX, 205, -3205);

		


		
		//App->objects->AddObject(OBJECT_TYPES::UPGRADE, 60, 150);

		//Turret
		
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 7, -576, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 129, -616, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 193, -678, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 130, -1002, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 202, -2017, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 10, -2027, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 74, -2035, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 144, -2043, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 178, -2065, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 108, -2073, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 42, -2073, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 18, -2115, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 98, -2121, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 154, -2113, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 206, -2145, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 5, -2153, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 76, -2161, MOVEMENT_TYPES::NO_MOVEMENT);
		App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 140, -2169, MOVEMENT_TYPES::NO_MOVEMENT);

		App->enemies->AddEnemy(BEATLE, 100, 100, NO_MOVEMENT);

		//Car
		//App->enemies->AddEnemy(ENEMY_TYPES::CAR, 150, -200);

		//BIG TURRETS
		//first(left)
		App->enemies->AddEnemy(ENEMY_TYPES::BIG_TURRET_RIGHT, 0, -1345, MOVEMENT_TYPES::NO_MOVEMENT);
		//second(right)
		App->enemies->AddEnemy(ENEMY_TYPES::BIG_TURRET_LEFT, 162, -1632, MOVEMENT_TYPES::NO_MOVEMENT);

		//GOLDEN TURRETS
		//left turret
		App->enemies->AddEnemy(ENEMY_TYPES::GOLDEN_TURRET, 40, -3040, MOVEMENT_TYPES::NO_MOVEMENT);
		//right turret
		App->enemies->AddEnemy(ENEMY_TYPES::GOLDEN_TURRET, 180, -3040, MOVEMENT_TYPES::NO_MOVEMENT);
		//VOLUMES
		//Blue Ship
		//blue ship left
		App->volumes->AddVolume(App->volumes->blue_ship_left, 0, -195);
		//blue ship right
		App->volumes->AddVolume(App->volumes->blue_ship_right, 158, -147);

		//Columns
		//column 1
		App->volumes->AddVolume(App->volumes->column_3, 127, -722);
		//column 2
		App->volumes->AddVolume(App->volumes->column_2, 190, -786);
		//column 3
		App->volumes->AddVolume(App->volumes->column_1, 0, -916);
		//column 4
		App->volumes->AddVolume(App->volumes->column_3, 160, -1075);
		//column 5
		App->volumes->AddVolume(App->volumes->column_1, 63, -1748);
		//column 6
		App->volumes->AddVolume(App->volumes->column_3, 191, -1780);
		//column 7
		App->volumes->AddVolume(App->volumes->column_2, 0, -1812);
		//column 8
		App->volumes->AddVolume(App->volumes->column_2, 95, -1908);

		//Door Walls
		//left wall
		App->volumes->AddVolume(App->volumes->door_wall_left, 0, -3130);
		//right wall
		App->volumes->AddVolume(App->volumes->door_wall_right, 164, -3130);

		//TEST ZONE
		//App->particles->AddParticle(App->particles->big_turret_fire, 150, 150,COLLIDER_NONE,UNDEFINED);
		//App->enemies->AddEnemy(ENEMY_TYPES::BIG_TURRET_LEFT, 100, 100, MOVEMENT_TYPES::NO_MOVEMENT);
		//App->particles->AddParticle(App->particles->partial_damage, 100, 100, COLLIDER_NONE, UNDEFINED);
		//App->collision->AddCollider({ 100, 100, 50, 50 }, COLLIDER_WALL);
		
		//App->enemies->AddEnemy(ENEMY_TYPES::TINY_TURRET, 20, 100, MOVEMENT_TYPES::NO_MOVEMENT);

		// App->enemies->AddEnemy(ENEMY_TYPES::BIG_TURRET_LEFT, 100, 100, MOVEMENT_TYPES::NO_MOVEMENT);
		// App->enemies->AddEnemy(ENEMY_TYPES::GOLDEN_TURRET, 50, 100, MOVEMENT_TYPES::NO_MOVEMENT);
		// App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 150, 100, MOVEMENT_TYPES::NO_MOVEMENT);
		// App->enemies->AddEnemy(ENEMY_TYPES::GOLDEN_TURRET, 50, 100, MOVEMENT_TYPES::NO_MOVEMENT);

		//App->enemies->AddEnemy(ENEMY_TYPES::CAR, 50, -100, MOVEMENT_TYPES::NO_MOVEMENT);

		

		

		//App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 50, 50);
		//App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 100, 50);
		//App->objects->AddObject(OBJECT_TYPES::ENERGY_BOX, 150, 50);
		



	return true;
}

// Update: draw background
update_status Module_lvl_1::Update()
{
	
	if (IsEnabled() == true){
	
		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, -3570, &background); // lvl 1 background
		

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
			App->change_scene->ChangeScene(App->lvl_1, App->welcome, 1.0f);
		}
	}

	return UPDATE_CONTINUE;
}

bool Module_lvl_1::CleanUp()
{
	LOG("Unloading lvl 1 stage");
	//DisableMusic
	Mix_FadeOutMusic(500);

	//Disable Collisions
	App->collision->Disable();
	//Disable Player
	App->player->Disable();
	//Disable Enemies
	App->enemies->Disable();
	//Disable Particles
	App->particles->Disable();
	//Disable Objects
	App->objects->Disable();
	//Disable Textures
	App->textures->Disable();
	//Volumes disable
	App->volumes->Disable();
	//UI dusable
	App->interfice->Disable();
	//	Counters disable
	App->fonts->Disable();
	
	return true;
}