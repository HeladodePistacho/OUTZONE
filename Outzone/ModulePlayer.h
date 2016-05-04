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
	//Miliseconds since the last shot
	Uint32 last_time;
	//Rotation timing
	Uint32 rotation_vel;
	//Miliseconds since the last rotation
	Uint32 last_rotation;
	
	
	//ANIMATIONS
	//Current animation
	Animation* current_animation = nullptr;
	//LASER
	//AFK
	Animation idle_up;
	Animation idle_up_right;
	Animation idle_right;
	Animation idle_down_right;
	Animation idle_up_left;
	Animation idle_down_left;
	Animation idle_left;
	Animation idle_down;
	//Movement
	Animation up;
	Animation up_right;
	Animation right;
	Animation down_right;
	Animation up_left;
	Animation down_left;
	Animation left;
	Animation down;

	//SHOTGUN
	//AFK
	Animation shotgun_AFK;
	//Movement
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