#ifndef __UPFRADE__
#define __UPGRADE__

#include "Object.h"
#include "ModuleParticles.h"

class Upgrade : public Object
{
private:
	Animation flash;
public:
	Upgrade(int x, int y);
};

#endif 