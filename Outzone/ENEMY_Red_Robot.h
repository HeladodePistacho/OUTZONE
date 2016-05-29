#ifndef __RED_ROBOT_H__
#define __RED_ROBOT_H__

#include "Enemy.h"
#include "ModuleParticles.h"
#include "Path.h"
#include "ModuleEnemies.h"

class ENEMY_Red_Robot : public Enemy
{
private:

	//statick animations
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

	//movement animations
	Animation mov_down;
	Animation mov_left;
	Animation mov_right;
	Animation mov_up;
	Animation mov_down_left;
	Animation mov_down_right;
	Animation mov_up_left;
	Animation mov_up_right;

	Animation hit_down;
	Animation hit_left;
	Animation hit_right;
	Animation hit_up;
	Animation hit_midle_down_right;
	Animation hit_midle_down_right_bot;
	Animation hit_midle_down_right_top;
	Animation hit_midle_down_left;
	Animation hit_midle_down_left_bot;
	Animation hit_midle_down_left_top;
	Animation hit_midle_up_right;
	Animation hit_midle_up_right_bot;
	Animation hit_midle_up_right_top;
	Animation hit_midle_up_left;
	Animation hit_midle_up_left_bot;
	Animation hit_midle_up_left_top;


	Animation* anim = Enemy::enemy_animation;

	Path path;
	iPoint original_position;
	iPoint last_position;
	int original_y = 0;


public:

	ENEMY_Red_Robot(int x, int y, MOVEMENT_TYPES type);

	void Move();
	void Attack();
	void Focus();
	bool Is_Dead();
	void hitmarker();
	void return_from_hitmarker();

	bool hit = false;
	int delay;
	int return_idle = 0;
	MOVEMENT_TYPES basic_robot_movement;
};

#endif 