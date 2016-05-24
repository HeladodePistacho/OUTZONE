#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "Module_lvl_1.h"
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
#include "ModuleVolumes.h"
Application::Application()
{

	uint num = 0;
	modules[num++] = window = new ModuleWindow();
	modules[num++] = render = new ModuleRender();
	modules[num++] = input = new ModuleInput();
	modules[num++] = textures = new ModuleTextures();
	modules[num++] = lvl_1 = new Module_lvl_1();
	modules[num++] = audio = new ModuleAudio();
	modules[num++] = welcome = new Module_Welcome();
	modules[num++] = congrats = new Module_Congrats();
	modules[num++] = gameover = new Module_GameOver();
	modules[num++] = objects = new ModuleObjects();
	modules[num++] = enemies = new ModuleEnemies();
	modules[num++] = particles = new ModuleParticles();
	modules[num++] = collision = new ModuleCollision();
	modules[num++] = player = new ModulePlayer();
	modules[num++] = volumes = new ModuleVolumes();
	modules[num++] = interfice = new ModuleInterfice();
	modules[num++] = change_scene = new ModuleChangeScene();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	audio->Disable();
	player->Disable();
	interfice->Disable();
	particles->Disable();
	enemies->Disable();
	lvl_1->Disable();
	congrats->Disable();
	gameover->Disable();
	collision->Disable();
	objects->Disable();
	volumes->Disable();

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