#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGameOver.h"
#include "Module_Welcome.h"
#include "ModuleChangeScene.h"
#include "ModuleInput.h"

Module_GameOver::Module_GameOver()
{
	// Congrats UI
	background.x = 0;
	background.y = 0;
	background.w = 240;
	background.h = 320;
}

Module_GameOver::~Module_GameOver(){}

bool Module_GameOver::Start()
{
	LOG("Loading Game Over Scene");
	//Load Background
	graphics = App->textures->Load("Game_Over.png");
	//Init Audio
	audio_Game_Over = App->audio->Load("game_over.ogg");
	Mix_FadeInMusicPos(audio_Game_Over, 1, 2000, 1);
	Mix_PlayMusic(audio_Game_Over, -1);
	//Camera
	App->render->camera.y = 0;
	return true;
}
// Update: draw background
update_status Module_GameOver::Update()
{

	if (IsEnabled() == true){

		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, 0, &background, 0.75f);
		if (App->input->keyboard[SDL_SCANCODE_SPACE]){
			App->change_scene->ChangeScene(App->gameover, App->welcome, 1.0f);

		}
	}
	return UPDATE_CONTINUE;
}

bool Module_GameOver::CleanUp()
{
	LOG("Unloading Congrats");
	App->textures->Disable();
	return true;
}