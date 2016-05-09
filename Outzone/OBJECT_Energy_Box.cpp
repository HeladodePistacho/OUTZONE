#include "Application.h"
#include "OBJECT_Energy_Box.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleObjects.h"
Energy_Box::Energy_Box(int x, int y) : Object(x, y)
{
	box.PushBack({ 0, 0, 41, 41 });
	flash.PushBack({ 130, 12, 16, 16 });
	flash.PushBack({ 130, 32, 16, 16 });
	flash.speed = 0.25f;
	object_animation = &box;
	type = ENERGY_BOX;
	collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_CHEST, (Module*)App->objects);
}

void Energy_Box::Update(){
	position.x += 8;
	position.y += 10;
	object_animation = &flash;
	App->collision->EraseCollider(collider);
	collider = App->collision->AddCollider({ position.x, position.y, 15, 15 }, COLLIDER_TYPE::COLLIDER_OBJECT, (Module*)App->objects);
}