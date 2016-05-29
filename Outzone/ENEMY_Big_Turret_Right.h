#ifndef _BIG_TURRET_RIGHT_
#define _BIG_TURRET_RIGHT_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Path.h"

class ENEMY_Big_Turret_Right : public Enemy{
private:

	//statik animations
	Animation idle;
	Animation hit;
	uint direction;
	Animation* anim = Enemy::enemy_animation;

public:
	ENEMY_Big_Turret_Right(int x, int y);

	void Attack();
	void hitmarker();
	bool Is_Dead();
	void return_from_hitmarker();

	int return_idle = 0;
	int delay;

};

#endif