#ifndef _CAR_
#define _CAR_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleVolumes.h"
#include "Path.h"

class ENEMY_Car : public Enemy{
private:
	//Draw data
	Animation stoped;
	Animation down;
	Animation hit;
	Animation* anim = Enemy::enemy_animation;
	Uint32 road_rate;
	Uint32 last_road;

	//Position data
	Path path;
	iPoint original_position;
	iPoint last_position;
	int original_y = 0;

	//Enemy Spawn Data
	unsigned int capacity;
	Uint32 spawn_rate;
	Uint32 last_spawn;

public:
	ENEMY_Car(int x, int y, MOVEMENT_TYPES type);
	void Move();
	void Drop();
	bool Is_Dead();
	void hitmarker();

	MOVEMENT_TYPES car_movement;

};
#endif