#include "Application.h"
#include "ENEMY_Beatle.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Beatle::ENEMY_Beatle(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
{


	original_position = position;


	if (basic_robot_movement == TYPE_DOWN_RIGHT)
	{
		path.PushBack({ 0.0f, 0.75f }, 150, anim);
		path.PushBack({ 0.75f, 0.5f }, 300, anim);
	}
	if (basic_robot_movement == TYPE_DOWN)
	{
		path.PushBack({ 0.0f, 0.75f }, 150, anim);
	}

	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 1000;
	last_time = 0;


	//enemy type
	live = 10;
	enemy_type = BEATLE;
}

void ENEMY_Beatle::Move()
{

	position = original_position + path.GetCurrentSpeed(&anim);

}

void ENEMY_Beatle::Attack()
{
	
}
