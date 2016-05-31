#include "Application.h"
#include "OBJECT_Car_Hole.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleObjects.h"

Car_Hole::Car_Hole(int x, int y) : Object(x, y)
{
	hole.PushBack({ 0, 104, 98, 121 });
	object_animation = &hole;
	type = CAR_HOLE;
}

void Car_Hole::Update(){
}