#ifndef __BASIC_ROBOT_H__
#define __BASIC_ROBOT_H__

#include "Enemy.h"
#include "ModuleParticles.h"
#include "Path.h"

class ENEMY_Basic_Robot : public Enemy
{
private:
	Animation down;
	Animation left;
	Animation right;
	Animation up;

	Animation* anim = Enemy::enemy_animation;

	Path path;
	iPoint original_position;
	int original_y = 0;


public:

	ENEMY_Basic_Robot(int x, int y);

	void Move();
	void Attack();
	void Focus();
};

#endif 