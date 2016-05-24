
#include "Application.h"
#include "ENEMY_Car.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleVolumes.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Car::ENEMY_Car(int x, int y) : Enemy(x, y)
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
	
	//MOVEMENT
	//Car path
	path.PushBack({ 0.0f, 0.0f }, 50, anim);
	path.PushBack({ 0.0f, 0.6f }, 150, anim);
	original_position.x = x;
	original_position.y = y;
	enemy_type = CAR;
	collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_SHIELD, (Module*)App->enemies);


	//DROP DATA
	last_spawn = 0;
	spawn_rate = 1000;
	capacity = 5;
	//ROAD DATA
	last_road = 0;
	road_rate = 300;
	//current time
	current_time = SDL_GetTicks();

	
	
	

}

void ENEMY_Car::Move()
{
	current_time = SDL_GetTicks();
	if (path.current_speed.y == 0){
		App->volumes->AddVolume(App->volumes->car_cover, position.x + 4, position.y);
		enemy_animation = &stoped;
	}
	else{
		App->volumes->AddVolume(App->volumes->car_cover, position.x + 4, position.y + 1);
		if (current_time > last_road + road_rate){
			App->particles->AddParticle(App->particles->car_road, position.x +2, position.y + 20, COLLIDER_NONE, UNDEFINED);
			last_road = current_time;
		}
		enemy_animation = &down;
	}
	if (capacity)Drop();
	position = original_position + path.GetCurrentSpeed(&anim);
	
}

void ENEMY_Car::Drop(){
	current_time = SDL_GetTicks();
	if (current_time > last_spawn + spawn_rate && enemy_animation == &down){
		if (capacity == 1){
			//Add red enemy
		}
		else{
			//App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x + 20, position.y, MOVEMENT_TYPES::NO_MOVEMENT);
		}
		last_spawn = current_time;
		capacity--;
	}
}