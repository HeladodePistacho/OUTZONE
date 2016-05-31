#ifndef __ModuleObjects__
#define __ModuleObjects__

#include "Module.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_OBJECTS 50

enum OBJECT_TYPES
{
	UNKNOWN,
	CHANGE_BOX,
	UPGRADE,
	ENERGY_BOX,
	CAR_RAIL,
	BOMB,
	CAR_HOLE
};

struct SDL_Texture;
class Object;

struct ObjectInfo
{
	OBJECT_TYPES type = OBJECT_TYPES::UNKNOWN;
	int x, y;
};

class ModuleObjects : public Module
{
public:

	ModuleObjects();
	~ModuleObjects();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddObject(OBJECT_TYPES type, int x, int y);


private:

	void SpawnObject(const ObjectInfo& info);

private:

	ObjectInfo queue[MAX_OBJECTS];
	Object* objects[MAX_OBJECTS];
	SDL_Texture* sprites;
	Mix_Chunk* Power_up = nullptr;
	Mix_Chunk* Energy_fx = nullptr;

};

#endif