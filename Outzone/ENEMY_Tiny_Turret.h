#ifndef _TINY_TURRET_
#define _TINY_TURRET_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "Path.h"

class ENEMY_Tiny_Turret : public Enemy{
private:

	//statik animations
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
public:
	ENEMY_Tiny_Turret(int x, int y);

	void Focus();

};

#endif