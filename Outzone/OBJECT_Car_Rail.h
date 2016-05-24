#ifndef __CAR_RAIL__
#define __CAR_RAIL__

#include "Object.h"
#include "ModuleParticles.h"

class Car_Rail : public Object
{
private:
	Animation rail;
public:
	Car_Rail(int x, int y);
	void Update();
};

#endif 