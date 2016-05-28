#ifndef _BIG_TURRET_LEFT_
#define _BIG_TURRET_LEFT_
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Path.h"

class ENEMY_Big_Turret_Left : public Enemy{
private:

	//statik animations
	Animation idle;
	Animation hit;
	uint direction;
	Animation* anim = Enemy::enemy_animation;
public:
	ENEMY_Big_Turret_Left(int x, int y);

	void Attack();
	bool Is_Dead();

};

#endif