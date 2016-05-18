#include "Application.h"
#include "ENEMY_Car.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Car::ENEMY_Car(int x, int y) : Enemy(x, y)
{
	stoped.PushBack({ 5,283,80,126 });
	down.PushBack({ 95, 284, 79, 125 });
	down.PushBack({ 190, 284, 78, 124 });
	down.PushBack({ 189, 284, 78, 125 });
	down.speed = 0.2f;
	down.loop = true;

	path.PushBack({ 0.0f, 0.0f }, 300, anim);
	path.PushBack({ 0.0f, 0.6f }, 150, anim);

	last_spawn = 0;
	spawn_rate = 200;
	
	current_time = SDL_GetTicks();
}

void ENEMY_Car::Move()
{
	Drop();
	if (path.current_speed.y == 0){
		if(collider!=nullptr)App->collision->EraseCollider(collider);
		collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_SHIELD, (Module*)App->enemies);
		
		enemy_animation = &stoped;
	}
	else{
		if (collider != nullptr)App->collision->EraseCollider(collider);
		collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
		
		enemy_animation = &down;
	}
	position = original_position + path.GetCurrentSpeed(&anim);
}

void ENEMY_Car::Drop(){
	//current_time = SDL_GetTicks();
	if (current_time > last_spawn + spawn_rate && enemy_animation == &down){
		App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, last_position.x, last_position.y, MOVEMENT_TYPES::TYPE_DOWN_RIGHT);
		last_spawn = current_time;
	}
}