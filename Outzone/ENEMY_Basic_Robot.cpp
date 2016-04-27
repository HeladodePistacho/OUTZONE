#include "Application.h"
#include "ENEMY_Basic_Robot.h"
#include "ModuleCollision.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Basic_Robot::ENEMY_Basic_Robot(int x, int y) : Enemy(x, y)
{


	walk.PushBack({ 109, 176, 27, 32 });

	original_position = position;

	path.PushBack({ 0.0f, 0.8f }, 150, &walk);
	path.PushBack({ 0.5f, 0.8f }, 300, &walk);
	
	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 500;
	last_time = 0;

}

void ENEMY_Basic_Robot::Move()
{

	position = original_position + path.GetCurrentSpeed(&animation);
}

void ENEMY_Basic_Robot::Attack()
{
	current_time = SDL_GetTicks();
	if (current_time >= last_time + fire_rate){

		//shot

	}
}

