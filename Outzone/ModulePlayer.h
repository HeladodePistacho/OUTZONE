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
	void Reset();

public:
	//TEXTURES
	SDL_Texture* graphics = nullptr;
	//COLLIDER
	Collider* body;
	
	//TIME DATA
	//Laser Weapon
	Uint32 laser_fire_rate;
	//Shotgun Weapon
	Uint32 shotgun_fire_rate;
	//Miliseconds since the init
	Uint32 current_time;
	//Miliseconds since the last timed action
	Uint32 last_time;
	
	
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

	//PLAYER DATA
	//Coordenades
	fPoint position;
	//Weapon Equiped
	bool shotgun = false;
	//Live state
	bool destroyed = false;
	//win or lose
	bool result = false;
	//??
	int last_position = 220;
	
};

#endif