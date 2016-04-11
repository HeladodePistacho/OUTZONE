#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_Welcome.h"
#include "Module_lvl_1.h"
#include "ModuleChangeScene.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

Module_Welcome::Module_Welcome()
{
	// Welcome UI
	background.x = 0;
	background.y = 0;
	background.w = 240;
	background.h = 320;
}

Module_Welcome::~Module_Welcome(){}

bool Module_Welcome::Start()
{
	LOG("Loading background assets");
	graphics = App->textures->Load("Welcome_Screen.png");
	App->render->escalated_screen = 0;

	return true;
}
// Update: draw background
update_status Module_Welcome::Update()
{

	if (IsEnabled() == true){
		
		// Draw everything --------------------------------------
		App->render->Blit(graphics, 0, 0, &background, 0.75f);
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
			App->change_scene->ChangeScene(App->welcome, App->lvl_1, 1.0f);

		}
	}
	return UPDATE_CONTINUE;
}

bool Module_Welcome::CleanUp()
{
	LOG("Unloading lvl 1 stage");

	App->render->escalated_screen = SCREEN_SIZE * App->lvl_1->map_size * 1.2f;
	return true;
}