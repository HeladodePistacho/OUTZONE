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
	Animation idle;
	Animation shoot;

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

};

#endif