#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_lvl_1.h"
#include "Module_lvl_2.h"
#include "ModuleChangeScene.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"

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
		//Init Audio
		audio_lvl_1 = App->audio->Load("1st_Level_Theme.ogg");
		Mix_FadeInMusicPos(audio_lvl_1, 1, 2000, 1);
		Mix_PlayMusic(audio_lvl_1, -1);
		//Enable Collisions
		App->player->Enable();
		App->collision->Enable();

		//Colliders
		App->collision->AddCollider({ 0, 3410, 95, 195 }, COLLIDER_WALL);//blue ship
		App->collision->AddCollider({ 178, 3429, 62, 116 }, COLLIDER_WALL);//blue ship
		App->collision->AddCollider({ 130, 2882, 29, 27 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 194, 2882, 30, 21 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, 2689, 31, 28 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 160, 2536, 32, 20 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, 2215, 123, 144 }, COLLIDER_WALL);//turret wall
		App->collision->AddCollider({ 0, 2354, 28, 36 }, COLLIDER_WALL);//turret wall
		App->collision->AddCollider({ 199, 2216, 41, 141 }, COLLIDER_WALL);//turret wall
		App->collision->AddCollider({ 0, 1932, 56, 137 }, COLLIDER_WALL);//turret wall 2(pipiru)
		App->collision->AddCollider({ 137, 1930, 103, 138 }, COLLIDER_WALL);//turret wall 2
		App->collision->AddCollider({ 65, 1857, 30, 27 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 193, 1826, 30, 27 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, 1790, 31, 29 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 96, 1699, 32, 36 }, COLLIDER_WALL);//column
		App->collision->AddCollider({ 0, 465, 91, 55 }, COLLIDER_WALL);//boss wall
		App->collision->AddCollider({ 165, 465, 75, 64 }, COLLIDER_WALL);//boss wall


	return true;
}

// Update: draw background
update_status Module_lvl_1::Update()
{
	
	if (IsEnabled() == true){
	
		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, -3570-background.y*2.5f, &background, 0.75f); // lvl 1 background
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
			App->change_scene->ChangeScene(App->lvl_2, App->lvl_1, 1.0f);
		}
	}

	return UPDATE_CONTINUE;
}

bool Module_lvl_1::CleanUp()
{
	LOG("Unloading lvl 1 stage");
	Mix_FadeOutMusic(500);
//<<<<<<< HEAD

	
//=======
	//Disable Collisions
	App->collision->Disable();
	App->player->Disable();
	App->textures->Disable();
//>>>>>>> origin/master
	App->render->escalated_screen = SCREEN_SIZE * App->lvl_2->map_size * 1.25f;
	return true;
}