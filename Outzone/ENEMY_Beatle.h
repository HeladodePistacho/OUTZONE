#ifndef _BEATLE_
#define _BEATLE_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Path.h"

class ENEMY_Beatle : public Enemy
{
private:

	//statik animations
	Animation movement;
	Animation shoot;
	Animation hit;

	MOVEMENT_TYPES basic_robot_movement;

	iPoint bullet_speed;
	Animation* anim = Enemy::enemy_animation;

	Path path;
	iPoint original_position;
	iPoint last_position;

public:
	ENEMY_Beatle(int x, int y, MOVEMENT_TYPES type);

	void Move();
	void Attack();
	bool Is_Dead();
	void hitmarker();
	void return_from_hitmarker();

	int delay;
	int return_idle = 0;
};

#endif