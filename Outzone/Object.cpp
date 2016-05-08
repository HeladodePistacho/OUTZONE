#include "Application.h"
#include "Object.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Object::Object(int x, int y) :position(x, y), collider(nullptr){}

Object::~Object()
{
	if (collider != nullptr){
		App->collision->EraseCollider(collider);
	}
}

const Collider* Object::GetCollider()const
{
	return collider;
}

void Object::Draw(SDL_Texture* sprites){
	if (collider != nullptr){
		collider->SetPos(position.x, position.y);
	}
	//App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}
