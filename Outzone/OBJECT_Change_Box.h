#ifndef __CHANGE_BOX__
#define __CHANGE_BOX__

#include "Object.h"
#include "ModuleParticles.h"

class Change_Box : public Object
{
private:
	Animation flash;
public:
	Change_Box(int x, int y);
};

#endif 