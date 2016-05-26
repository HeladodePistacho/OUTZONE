#ifndef __BOMB__
#define __BOMB__

#include "Object.h"
#include "ModuleParticles.h"

class Bomb : public Object
{
private:
	Animation flash;
public:
	Bomb(int x, int y);
};

#endif 