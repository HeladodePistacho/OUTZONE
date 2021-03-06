#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class ModuleInterfice;
class ModuleObjects;
class ModuleParticles;
class ModuleEnemies;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleCollision;
class Module_lvl_1;
class ModulePlayer;
class ModuleAudio;
class ModuleChangeScene;
class Module_Welcome;
class Module_Congrats;
class Module_GameOver;
class ModuleVolumes;
class ModuleFonts;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	Module_lvl_1* lvl_1;
	ModulePlayer* player;
	ModuleAudio* audio;
	ModuleChangeScene* change_scene;
	Module_Welcome* welcome;
	Module_Congrats* congrats;
	Module_GameOver* gameover;
	ModuleCollision* collision;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleObjects* objects;
	ModuleInterfice* interfice;
	ModuleVolumes* volumes;
	ModuleFonts* fonts;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__