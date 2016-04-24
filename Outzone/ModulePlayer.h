#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Collider* body;
	
	
	//ANIMATIONS
	//Current animation
	Animation* current_animation = nullptr;
	//AFK
	Animation idle;
	Animation shotgun_AFK;
	//Movement
	Animation up;
	Animation up_right;
	Animation right;
	Animation down_right;
	Animation up_left;
	Animation down_left;
	Animation left;
	Animation down;
	Animation shotgun_walk;

	fPoint position;
	bool shotgun = false;
	bool destroyed = false;

	int last_position = 220;
};

#endif