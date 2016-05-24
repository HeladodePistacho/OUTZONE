#include "Application.h"
#include "OBJECT_Car_Rail.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleObjects.h"

Car_Rail::Car_Rail(int x, int y) : Object(x, y)
{
	rail.PushBack({ 6, 62, 66, 26 });
	object_animation = &rail;
	type = CAR_RAIL;
}

void Car_Rail::Update(){
}