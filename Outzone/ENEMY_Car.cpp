
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
	stoped.PushBack({ 5, 283, 80, 126 });
	down.PushBack({ 95, 284, 79, 125 });
	down.PushBack({ 190, 284, 78, 124 });
	down.PushBack({ 189, 284, 78, 125 });
	down.speed = 0.2f;
	down.loop = true;

	//Cover
	cover.volume_sprite.PushBack({ 5, 47, 80, 80 });
	cover.volume_sprite.loop = true;
	//Car path
	path.PushBack({ 0.0f, 0.0f }, 50, anim);
	path.PushBack({ 0.0f, 0.6f }, 150, anim);

	last_spawn = 0;
	spawn_rate = 1000;
	capacity = 5;

	current_time = SDL_GetTicks();

	//enemy type
	enemy_type = CAR;
}

void ENEMY_Car::Move()
{
	if (path.current_speed.y == 0){
		if (collider != nullptr)App->collision->EraseCollider(collider);
		collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_SHIELD, (Module*)App->enemies);

		enemy_animation = &stoped;
	}
	else{
		if (collider != nullptr)App->collision->EraseCollider(collider);
		collider = App->collision->AddCollider({ 0, 0, 70, 120 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

		enemy_animation = &down;
	}
	if (capacity)Drop();
	position = original_position + path.GetCurrentSpeed(&anim);

	App->volumes->AddVolume(cover, position.x + 10, position.y + 10);
	cover.position.x = position.x + 10;
	cover.position.y = position.y + 10;

}

void ENEMY_Car::Drop(){
	current_time = SDL_GetTicks();
	if (current_time > last_spawn + spawn_rate && enemy_animation == &down){
		if (capacity == 1){
			//Add red enemy
		}
		else{
			App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ROBOT, position.x, position.y, MOVEMENT_TYPES::NO_MOVEMENT);
		}
		last_spawn = current_time;
		capacity--;
	}
}