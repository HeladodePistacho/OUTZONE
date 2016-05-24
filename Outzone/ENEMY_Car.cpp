
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
	//Animations
	stoped.PushBack({ 3, 283, 80, 126 });
	down.PushBack({ 94, 284, 79, 125 });
	down.PushBack({ 188, 284, 78, 124 });
	down.PushBack({ 188, 284, 78, 125 });
	down.speed = 0.05f;
	down.loop = true;

	//Cover
	cover.volume_sprite.PushBack({ 0,205, 46,67 });
	cover.volume_sprite.loop = false;
	//Car path
	path.PushBack({ 0.0f, 0.0f }, 50, anim);
	path.PushBack({ 0.0f, 0.6f }, 150, anim);

	last_spawn = 0;
	spawn_rate = 1000;
	capacity = 5;

	current_time = SDL_GetTicks();

	//enemy type
	enemy_type = CAR;
	//defines original position
	original_position.x = x;
	original_position.y = y;
	collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_SHIELD, (Module*)App->enemies);

}

void ENEMY_Car::Move()
{
	if (path.current_speed.y == 0){
		App->volumes->AddVolume(cover, position.x + 13, position.y);
		enemy_animation = &stoped;
	}
	else{
		App->volumes->AddVolume(cover, position.x + 13, position.y + 1);
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