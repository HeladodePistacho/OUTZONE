#ifndef __ENERGY_BOX__
#define __ENERGY_BOX__

#include "Object.h"
#include "ModuleParticles.h"

class Energy_Box : public Object
{
private:
	Animation box;
	Animation flash;
public:
	Energy_Box(int x, int y);
	void Update();
};

#endif 