#ifndef __lvl_2__
#define __lvl_2__

#include "Module.h"
#include "ModuleAudio.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class Module_lvl_2 : public Module
{
public:
	Module_lvl_2();
	~Module_lvl_2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	Mix_Music* audio_lvl_2 = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	uint map_size = 5279;
};

#endif