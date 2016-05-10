#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "Module_lvl_1.h"
#include "Module_lvl_2.h"
#include "ModulePlayer.h"
#include "Module_Welcome.h"
#include "Module_Congrats.h"
#include "ModuleChangeScene.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleGameOver.h"
#include "ModuleObjects.h"
#include "ModuleInterfice.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = lvl_1 = new Module_lvl_1();
	modules[5] = lvl_2 = new Module_lvl_2();
	modules[6] = audio = new ModuleAudio();
	modules[7] = change_scene = new ModuleChangeScene();
	modules[8] = welcome = new Module_Welcome();
	modules[9] = congrats = new Module_Congrats();
	modules[10] = gameover = new Module_GameOver();
	modules[11] = enemies = new ModuleEnemies();
	modules[12] = objects = new ModuleObjects();
	modules[13] = particles = new ModuleParticles();
	modules[14] = collision = new ModuleCollision();
	modules[15] = player = new ModulePlayer();
	modules[16] = interfice = new ModuleInterfice();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	player->Disable();
	interfice->Disable();
	particles->Disable();
	enemies->Disable();
	lvl_1->Disable();
	lvl_2->Disable();
	congrats->Disable();
	gameover->Disable();
	collision->Disable();
	objects->Disable();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}