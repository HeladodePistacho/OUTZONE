#include "Application.h"
#include "ENEMY_Beatle.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Beatle::ENEMY_Beatle(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
{

	movement.PushBack({ 0, 760, 44, 41 });
	movement.PushBack({ 52, 760, 46, 47 });

	enemy_animation = &movement;

	original_position = position;

	//Path1
	/*
	path.PushBack({ -2.0f, 0.0f }, 65, anim);
	path.PushBack({ -1.975f, 0.312f }, 7, anim);
	path.PushBack({ -1.902f, 0.618f }, 7, anim);
	path.PushBack({ -1.782f, 0.907f }, 7, anim);
	path.PushBack({ -1.618f, 1.175f }, 7, anim);
	path.PushBack({ -1.414f, 1.414f }, 7, anim);
	path.PushBack({ -1.175f, 1.618f }, 7, anim);
	path.PushBack({ -0.907f, 1.782f }, 7, anim);
	path.PushBack({ -0.312f, 1.975f }, 7, anim);
	path.PushBack({ 0.312f, 1.975f }, 7, anim);
	path.PushBack({ 0.618f, 1.902f }, 7, anim);
	path.PushBack({ 1.175f, 1.618f }, 7, anim);
	path.PushBack({ 1.414f, 1.414f }, 7, anim);
	path.PushBack({ 1.618f, 1.175f }, 7, anim);
	path.PushBack({ 1.782f, 0.907f }, 7, anim);
	path.PushBack({ 1.902f, 0.618f }, 7, anim);
	path.PushBack({ 1.975f, 0.312f }, 7, anim);
	path.PushBack({ 2.0f, 0.0f }, 200, anim);
	*/

	//Path2
	path.PushBack({ 2.0f, 0.0f }, 35, anim);
	path.PushBack({ 1.975f, 0.312f }, 7, anim);
	path.PushBack({ 1.902f, 0.618f }, 7, anim);
	path.PushBack({ 1.782f, 0.907f }, 7, anim);
	path.PushBack({ 1.618f, 1.175f }, 7, anim);
	path.PushBack({ 1.414f, 1.414f }, 7, anim);
	path.PushBack({ 1.175f, 1.618f }, 7, anim);
	path.PushBack({ 0.907f, 1.782f }, 7, anim);
	path.PushBack({ 0.312f, 1.975f }, 7, anim);

	path.PushBack({ -0.312f, 1.975f }, 7, anim);
	path.PushBack({ -0.618f, 1.902f }, 7, anim);
	path.PushBack({ -1.175f, 1.618f }, 7, anim);
	path.PushBack({ -1.414f, 1.414f }, 7, anim);
	path.PushBack({ -1.618f, 1.175f }, 7, anim);
	path.PushBack({ -1.782f, 0.907f }, 7, anim);
	path.PushBack({ -1.902f, 0.618f }, 7, anim);
	path.PushBack({ -1.975f, 0.312f }, 7, anim);

	path.PushBack({ -1.975f, -0.312f }, 7, anim);
	path.PushBack({ -1.902f, -0.618f }, 7, anim);
	path.PushBack({ -1.782f, -0.907f }, 7, anim);
	path.PushBack({ -1.618f, -1.175f }, 7, anim);
	path.PushBack({ -1.414f, -1.414f }, 7, anim);
	path.PushBack({ -1.175f, -1.618f }, 7, anim);
	path.PushBack({ -0.907f, -1.782f }, 7, anim);
	path.PushBack({ -0.312f, -1.975f }, 7, anim);

	path.PushBack({ 0.312f, -1.975f }, 7, anim);
	path.PushBack({ 0.618f, -1.902f }, 7, anim);
	path.PushBack({ 1.175f, -1.618f }, 7, anim);
	path.PushBack({ 1.414f, -1.414f }, 7, anim);
	path.PushBack({ 1.618f, -1.175f }, 7, anim);
	path.PushBack({ 1.782f, -0.907f }, 7, anim);
	path.PushBack({ 1.902f, -0.618f }, 7, anim);
	path.PushBack({ 1.975f, -0.312f }, 7, anim);

	path.PushBack({ 1.975f, 0.312f }, 7, anim);
	path.PushBack({ 1.902f, 0.618f }, 7, anim);
	path.PushBack({ 1.782f, 0.907f }, 7, anim);
	path.PushBack({ 1.618f, 1.175f }, 7, anim);
	path.PushBack({ 1.414f, 1.414f }, 7, anim);
	path.PushBack({ 1.175f, 1.618f }, 7, anim);
	path.PushBack({ 0.907f, 1.782f }, 7, anim);
	path.PushBack({ 0.312f, 1.975f }, 7, anim);

	path.PushBack({ -0.312f, 1.975f }, 7, anim);
	path.PushBack({ -0.618f, 1.902f }, 7, anim);
	path.PushBack({ -1.175f, 1.618f }, 7, anim);
	path.PushBack({ -1.414f, 1.414f }, 7, anim);
	path.PushBack({ -1.618f, 1.175f }, 7, anim);
	path.PushBack({ -1.782f, 0.907f }, 7, anim);
	path.PushBack({ -1.902f, 0.618f }, 7, anim);
	path.PushBack({ -1.975f, 0.312f }, 7, anim);

	path.PushBack({ -2.0f, 0.0f }, 200, anim);
	

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
