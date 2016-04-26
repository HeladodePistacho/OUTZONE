#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_lvl_1.h"
#include "Module_lvl_2.h"
#include "ModuleChangeScene.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

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
		//Enable Collisions

		App->player->Enable();
		App->collision->Enable();
		App->enemies->Enable();
		App->player->Reset();
		

		//Colliders
		App->collision->AddCollider({ 0, -152, 95, 195}, COLLIDER_WALL);//blue ship left
		App->collision->AddCollider({ 0, -162, 48, 50 }, COLLIDER_WALL);//blue ship left
		App->collision->AddCollider({ 178, -132, 59, 86 }, COLLIDER_WALL);//blue ship right
		App->collision->AddCollider({ 178, -55, 62, 34 }, COLLIDER_WALL);//blue ship right
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

		App->collision->AddCollider({ 0, -1350, 30, 178 }, COLLIDER_WALL);//turret wall
		App->collision->AddCollider({ 30, -1350, 77, 142 }, COLLIDER_WALL);//turret wall
		App->collision->AddCollider({ 107, -1338, 16, 130 }, COLLIDER_WALL);
		App->collision->AddCollider({ 200, -1354, 40, 142 }, COLLIDER_WALL);//turret wall
		App->collision->AddCollider({ 0, -1640, 39, 140 }, COLLIDER_WALL);//turret wall 2(pipiru)
		App->collision->AddCollider({ 39, -1626, 18, 130 }, COLLIDER_WALL);
		App->collision->AddCollider({ 134, -1642, 103, 144 }, COLLIDER_WALL);//turret wall 2

		App->collision->AddCollider({ 0, -3128, 29, 81 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 29, -3116, 46, 61 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 184, -3116, 46, 61 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 230, -3128, 14, 78 }, COLLIDER_WALL);//boss wall

		App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, 100, -100);



	return true;
}

// Update: draw background
update_status Module_lvl_1::Update()
{
	
	if (IsEnabled() == true){
	
		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, -3570, &background); // lvl 1 background
		

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
			App->change_scene->ChangeScene(App->lvl_2, App->lvl_1, 1.0f);
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
	App->player->Disable();

	//disable particles
	App->particles->Disable();
	App->enemies->Disable();

	//Disable Textures
	App->textures->Disable();
	App->render->escalated_screen = SCREEN_SIZE * App->lvl_2->map_size * 1.25f;
	return true;
}