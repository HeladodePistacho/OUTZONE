#ifndef _GOLDEN_TURRET_
#define _GOLDEN_TURRET_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Path.h"

class ENEMY_Golden_Turret : public Enemy{
private:

	//statik animations
	Animation idle;
	Animation hit;
	uint direction;
	iPoint bullet_speed;
	Animation* anim = Enemy::enemy_animation;
public:
	ENEMY_Golden_Turret(int x, int y);

	void Attack();
	bool Is_Dead();
	void hitmarker();
	void return_from_hitmarker();

	int delay;
	int return_idle = 0;

};

#endif