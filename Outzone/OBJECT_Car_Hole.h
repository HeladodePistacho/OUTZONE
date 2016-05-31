#ifndef __CAR_HOLE__
#define __CAR_HOLE__

#include "Object.h"
#include "ModuleParticles.h"

class Car_Hole : public Object
{
private:
	Animation hole;
public:
	Car_Hole(int x, int y);
	void Update();
};

#endif 