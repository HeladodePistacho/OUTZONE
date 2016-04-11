#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_lvl_1.h"
#include "Module_lvl_2.h"
#include "ModuleChangeScene.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

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




// Load assets
bool Module_lvl_1::Start()
{
	
	LOG("Loading background assets");
		graphics = App->textures->Load("level1.png");
		audio_lvl_1 = App->audio->Load("1st_Level_Theme.ogg");

		Mix_FadeInMusicPos(audio_lvl_1, 1, 2000, 1);
		Mix_PlayMusic(audio_lvl_1, -1);

	return true;
}

// Update: draw background
update_status Module_lvl_1::Update()
{
	
	if (IsEnabled() == true){
	
		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, -3570, &background, 0.75f); // lvl 1 background
		

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
	
	App->render->escalated_screen = SCREEN_SIZE * App->lvl_2->map_size * 1.25f;
	return true;
}