#ifndef __ModuleWelcome_H__
#define __ModuleWelcome_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class Module_Welcome : public Module
{
public:
	Module_Welcome();
	~Module_Welcome();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;

};

#endif