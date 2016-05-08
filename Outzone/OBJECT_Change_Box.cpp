#include "Application.h"
#include "OBJECT_Change_Box.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Change_Box::Change_Box(int x, int y) : Object(x, y)
{
	flash.PushBack({ 109, 176, 27, 32 });
	collider = App->collision->AddCollider({ 0, 0, 20, 20 }, COLLIDER_TYPE::COLLIDER_OBJECT, (Module*)App->objects);
}