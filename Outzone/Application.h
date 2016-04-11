#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class Module_lvl_1;
class Module_lvl_2;
class ModulePlayer;
class ModuleAudio;
class ModuleChangeScene;
class Module_Welcome;
class Module_Congrats;
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
	Module_lvl_2* lvl_2;
	ModulePlayer* player;
	ModuleAudio* audio;
	ModuleChangeScene* change_scene;
	Module_Welcome* welcome;
	Module_Congrats* congrats;

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