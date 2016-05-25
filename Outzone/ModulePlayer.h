#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"

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

public:

	//Collision method
	void OnCollision(Collider* c1, Collider* c2);
	//Movement methods
	void Go_North(float);
	void Go_South(float);
	void Go_East(float);
	void Go_East_Up(float);
	void Go_East_Down(float);
	void Go_West(float);
	void Go_West_Up(float);
	void Go_West_Down(float);
	//Reset player data
	void Reset();

public:

	//TEXTURES
	SDL_Texture* graphics = nullptr;
	
	
	//COLLIDER
	Collider* body;
	
	
	//TIME DATA
	//Laser Weapon rate
	Uint32 laser_fire_rate;
	//Shotgun Weapon rate
	Uint32 shotgun_fire_rate;
	//Miliseconds since the init
	Uint32 current_time;
	//Miliseconds since the last shot
	Uint32 last_time;
	//Rotation timing
	Uint32 rotation_vel;
	//Miliseconds since the last rotation
	Uint32 last_rotation;
	//Energy segment live
	Uint32 energy_segment_live;
	//Last energy segment dead
	Uint32 last_segment;
	
	
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
	//Shotgun level
	uint shotgun_lvl;
	//Live state
	bool destroyed = false;
	//Win or Lose
	bool result = false;
	//Last position
	int last_position = 220;
	//God mode
	bool god_mode = false;


	//PLAYER FX
	Mix_Chunk* laser_fx = nullptr;
	Mix_Chunk* shotgun_fx = nullptr;
	Mix_Chunk* dead_fx = nullptr;


	//PLAYER INTERFICE
	//Current score
	char score_text[10];
	uint score = 0;
	int score_font = -1;
	//Top score
	char top_score_text[10];
	uint top_score = 500;
	//Lives
	char lives_text[4];
	uint lives = 2;
	int lives_font = -1;
	//Bombs
	uint bombs = 3;
	uint bombs_limit = 10;
	//Energy
	uint energy;
	uint energy_limit = 36;
	

	
};

#endif