#ifndef _CAR_
#define _CAR_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleVolumes.h"
#include "Path.h"

class ENEMY_Car : public Enemy{
private:
	Animation stoped;
	Animation down;
	Animation* anim = Enemy::enemy_animation;
	Volume cover;
	Path path;
	iPoint original_position;
	iPoint last_position;
	int original_y = 0;

	//Enemy Spawn Data
	unsigned int capacity;
	Uint32 spawn_rate;
	Uint32 last_spawn;
public:
	ENEMY_Car(int x, int y);
	void Move();
	void Drop();

};
#endif