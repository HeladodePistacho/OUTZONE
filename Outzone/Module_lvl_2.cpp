#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_lvl_1.h"
#include "Module_lvl_2.h"
#include "ModuleChangeScene.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

Module_lvl_2::Module_lvl_2()
{

	// Level 2 
	background.x = 0;
	background.y = 0;
	background.w = 240;
	background.h = 5279;

}

Module_lvl_2::~Module_lvl_2()
{}

// Load assets
bool Module_lvl_2::Start()
{
	LOG("Loading background assets");
	graphics = App->textures->Load("level2.png");
	audio_lvl_2 = App->audio->Load("2nd_Level_Theme.ogg");

	Mix_FadeInMusic(audio_lvl_2, 1, 500);
	Mix_PlayMusic(audio_lvl_2, -1);
	
	return true;
}

// Update: draw background
update_status Module_lvl_2::Update()
{
	if (IsEnabled() == true){
		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, -4940, &background, 0.75f); // lvl 2 background
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
			App->change_scene->ChangeScene(App->lvl_1, App->lvl_2, 1.0f);
		}
	}
	return UPDATE_CONTINUE;
}

bool Module_lvl_2::CleanUp()
{
	LOG("Unloading lvl 2 stage");
	App->render->escalated_screen = 0;
	Mix_FadeOutMusic(500);
	return true;
}