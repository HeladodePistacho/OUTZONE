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

	Animation midle_down_right;
	Animation midle_down_right_bot;
	Animation midle_down_right_top;
	Animation midle_down_left;
	Animation midle_down_left_bot;
	Animation midle_down_left_top;
	Animation midle_up_right;
	Animation midle_up_right_bot;
	Animation midle_up_right_top;
	Animation midle_up_left;
	Animation midle_up_left_bot;
	Animation midle_up_left_top;
	

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