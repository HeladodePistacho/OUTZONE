#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_Congrats.h"
#include "Module_Welcome.h"
#include "ModuleChangeScene.h"
#include "ModuleInput.h"

Module_Congrats::Module_Congrats()
{
	// Congrats UI
	background.x = 0;
	background.y = 0;
	background.w = 240;
	background.h = 320;
}

Module_Congrats::~Module_Congrats(){}

bool Module_Congrats::Start()
{
	LOG("Loading background assets");
	graphics = App->textures->Load("Congrats_Screen.png");

	return true;
}
// Update: draw background
update_status Module_Congrats::Update()
{

	if (IsEnabled() == true){

		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, 0, &background, 0.75f);
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
			App->change_scene->ChangeScene(App->congrats, App->welcome, 1.0f);

		}
	}
	return UPDATE_CONTINUE;
}

bool Module_Congrats::CleanUp()
{
	LOG("Unloading lvl 1 stage");
	return true;
}