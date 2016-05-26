#include "Application.h"
#include "OBJECT_Bomb.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleObjects.h"

Bomb::Bomb(int x, int y) : Object(x, y)
{
	flash.PushBack({ 95, 67, 17, 16 });
	flash.PushBack({ 122, 67, 16, 16 });
	flash.speed = 0.25f;
	object_animation = &flash;
	type = BOMB;
	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_OBJECT, (Module*)App->objects);
}