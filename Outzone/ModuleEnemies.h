#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"

#define MAX_ENEMIES 50

enum ENEMY_TYPES
{
	NO_TYPE,
	CAR,
	BASIC_ROBOT,
	RED_ROBOT,
	BLUE_ROBOT,
	TINY_TURRET,
	BIG_TURRET_LEFT,
	BIG_TURRET_RIGHT,
	GOLDEN_TURRET,
	BEATLE
};

enum MOVEMENT_TYPES
{
	NO_MOVEMENT,
	TYPE_DOWN,
	TYPE_DOWN_RIGHT,
	TYPE_DOWN_LEFT,
	TYPE_CIRCLE,
	TYPE_SEMI_CIRCLE,
	TYPE_DIAGONAL_LEFT,
	TYPE_DIAGONAL_LEFT_2,
	CAR_TYPE_1,
	CAR_TYPE_2,
	GET_OUT_CAR_1,
	GET_OUT_CAR_2,
	GET_OUT_CAR_3,
	GET_OUT_CAR_4,
	GET_OUT_CAR_5,
	GET_OUT_CAR_6,
	GET_OUT_CAR_7,
	GET_OUT_CAR_8
};

enum DIRECTION{
	RIGHT,
	LEFT,
	NONE
};

struct SDL_Texture;
class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	MOVEMENT_TYPES movement_type = MOVEMENT_TYPES::NO_MOVEMENT;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, MOVEMENT_TYPES m_type);
	

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif