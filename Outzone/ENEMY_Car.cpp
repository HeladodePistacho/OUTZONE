
#include "Application.h"
#include "ENEMY_Car.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleVolumes.h"
#include "ModuleObjects.h"
#include "ModuleInterfice.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Car::ENEMY_Car(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), car_movement(type)
{
	//ANIMATIONS
	//Stop
	stoped.PushBack({ 3, 283, 80, 126 });
	//Move
	down.PushBack({ 94, 284, 79, 125 });
	down.PushBack({ 188, 284, 78, 124 });
	down.PushBack({ 188, 284, 78, 125 });
	down.speed = 0.05f;
	down.loop = true;
	//hit
	hit.PushBack({ 385, 283, 80, 125 });
	hit.speed = 0.1f;
	
	//MOVEMENT
	//Car path
	if (car_movement == CAR_TYPE_1)
	{
		path.PushBack({ 0.0f, 0.8f }, 50, anim);
		path.PushBack({ 0.0f, 0.0f }, 250, anim);
		path.PushBack({ 0.0f, 0.8f }, 1000, anim);
	}

	original_position.x = x;
	original_position.y = y;
	enemy_type = CAR;
	collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_SHIELD, (Module*)App->enemies);

	

	//DROP DATA
	last_spawn = 0;
	spawn_rate = 800;
	capacity = 6;
	//ROAD DATA
	last_road = 0;
	road_rate = 300;
	//current time
	current_time = SDL_GetTicks();

	
	live = 16;
	

}

void ENEMY_Car::Move()
{
	current_time = SDL_GetTicks();
	if (path.current_speed.y == 0)
	{
		App->volumes->AddVolume(App->volumes->car_cover, position.x + 4, position.y);
		enemy_animation = &stoped;
		
	}
	else{
		App->volumes->AddVolume(App->volumes->car_cover, position.x + 4, position.y + 1);
		if (current_time > last_road + road_rate){
			App->objects->AddObject(CAR_RAIL, position.x +2, position.y + 20);
			last_road = current_time;
		}
		enemy_animation = &down;
	}
	if (capacity)Drop();
	position = original_position + path.GetCurrentSpeed(&anim);
	
}

void ENEMY_Car::Drop(){
	current_time = SDL_GetTicks();
	if (current_time > last_spawn + spawn_rate && enemy_animation == &stoped)
	{
		if (car_movement == CAR_TYPE_1)
		{
		if (capacity == 1)
			App->enemies->AddEnemy(ENEMY_TYPES::RED_ROBOT, position.x + 20, position.y, MOVEMENT_TYPES::GET_OUT_CAR_6); //Add red enemy
	
		if (capacity == 6)
			App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x + 20, position.y, MOVEMENT_TYPES::GET_OUT_CAR_1);

		if (capacity == 5)
			App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x + 20, position.y , MOVEMENT_TYPES::GET_OUT_CAR_2);

		if (capacity == 4)
			App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x + 20, position.y, MOVEMENT_TYPES::GET_OUT_CAR_3);

		if (capacity == 3)
			App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x + 20, position.y, MOVEMENT_TYPES::GET_OUT_CAR_4);
		
		if (capacity == 2)
			App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x + 20, position.y, MOVEMENT_TYPES::GET_OUT_CAR_5);
	}
		last_spawn = current_time;
		capacity--;
	}
}

void ENEMY_Car::hitmarker()
{
	enemy_animation = &hit;
}

bool ENEMY_Car::Is_Dead()
{
	if (live <= 0)
	{
		App->particles->AddParticle(App->particles->car_hole, position.x - 5, position.y, COLLIDER_NONE, UNDEFINED);
		App->particles->AddParticle(App->particles->big_enemy_explosion, position.x - 30, position.y - 5, COLLIDER_NONE, UNDEFINED);
		App->interfice->score += 20;
		return true;
	}
	return false;
}