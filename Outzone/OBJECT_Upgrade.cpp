#include "Application.h"
#include "OBJECT_Upgrade.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleObjects.h"
Upgrade::Upgrade(int x, int y) : Object(x, y)
{
	flash.PushBack({ 88, 12 , 16, 16 });
	flash.PushBack({ 88, 33, 16, 16 });
	flash.speed = 0.25f;
	object_animation = &flash;
	type = UPGRADE;
	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_OBJECT, (Module*)App->objects);
}