#ifndef __ModuleGAMEOVER_H__
#define __ModuleGAMEOVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class Module_GameOver : public Module
{
public:
	Module_GameOver();
	~Module_GameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* audio_Game_Over = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;

};

#endif