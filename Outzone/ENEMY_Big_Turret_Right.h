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

	Animation* anim = Enemy::enemy_animation;
public:
	ENEMY_Big_Turret_Right(int x, int y);

	void Attack();

};

#endif