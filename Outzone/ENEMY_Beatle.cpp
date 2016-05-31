#include "Application.h"
#include "ENEMY_Beatle.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Beatle::ENEMY_Beatle(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
{

	movement.PushBack({ 0, 760, 44, 41 });
	movement.PushBack({ 52, 760, 46, 47 });
	
	shoot.PushBack({ 106, 760, 46, 47 });
	shoot.PushBack({ 163, 760, 45, 46 });
	shoot.PushBack({ 219, 760, 46, 47 });
	shoot.speed = 0.32f;

	movement.speed = 0.32f;

	hit.PushBack({ 0, 816, 44, 41 });

	enemy_animation = &movement;

	original_position = position;

	//Path1
	if (basic_robot_movement == TYPE_SEMI_CIRCLE_1)
	{
		path.PushBack({ -2.0f, 0.0f }, 60, anim);
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
	}
		
	if (basic_robot_movement == TYPE_SEMI_CIRCLE_2)
	{
		path.PushBack({ -2.0f, 0.0f }, 90, anim);
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
		path.PushBack({ 2.0f, 0.0f }, 2000, anim);
	}
	if (basic_robot_movement == TYPE_SEMI_CIRCLE_3)
	{
		path.PushBack({ -2.0f, 0.0f }, 120, anim);
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
		path.PushBack({ 2.0f, 0.0f }, 2000, anim);
	}
	if (basic_robot_movement == TYPE_SEMI_CIRCLE_4)
	{
		path.PushBack({ -2.0f, 0.0f }, 150, anim);
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
		path.PushBack({ 2.0f, 0.0f }, 2000, anim);
	}
	//Path2
	if (basic_robot_movement == TYPE_CIRCLE_1)
	{
		path.PushBack({ 2.0f, 0.0f }, 50, anim);
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

		path.PushBack({ -2.0f, 0.0f }, 2000, anim);
	}

	if (basic_robot_movement == TYPE_CIRCLE_2)
	{
		path.PushBack({ 2.0f, 0.0f }, 80, anim);
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

		path.PushBack({ -2.0f, 0.0f }, 2000, anim);
	}

	if (basic_robot_movement == TYPE_CIRCLE_3)
	{
		path.PushBack({ 2.0f, 0.0f }, 110, anim);
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

		path.PushBack({ -2.0f, 0.0f }, 2000, anim);
	}

	if (basic_robot_movement == TYPE_CIRCLE_4)
	{
		path.PushBack({ 2.0f, 0.0f }, 140, anim);
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

		path.PushBack({ -2.0f, 0.0f }, 2000, anim);
	}

	collider = App->collision->AddCollider({ 0, 0, 46, 46 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 700;
	last_time = fire_rate;


	//enemy type
	delay = 100;
	live = 10;
	enemy_type = BEATLE;
	
}

void ENEMY_Beatle::Move()
{

	position = original_position + path.GetCurrentSpeed(&anim);

}

void ENEMY_Beatle::Attack()
{
	
	current_time = SDL_GetTicks();

	if (current_time >= (last_time + (fire_rate - 100)))
		enemy_animation = &shoot;

	if (current_time >= last_time + fire_rate)
	{
		

		App->particles->AddParticle(App->particles->missile_impact, position.x + 13, position.y + 25, COLLIDER_ENEMY_SHOT, ENEMY_MISSILE);
		App->particles->AddParticle(App->particles->enemy_missile, position.x + 13, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_MISSILE);
		last_time = current_time;
	}

}

bool ENEMY_Beatle::Is_Dead()
{
	if (live <= 0)
	{
		App->particles->AddParticle(App->particles->big_enemy_explosion, position.x - 50, position.y - 50, COLLIDER_NONE, UNDEFINED);
		App->interfice->score += 1490;
		return true;
	}
	return false;

}

void ENEMY_Beatle::hitmarker()
{
	if (enemy_animation != &hit)
		enemy_animation = &hit;
}

void ENEMY_Beatle::return_from_hitmarker()
{
	if (enemy_animation != &movement || enemy_animation != &shoot)
	{
		if (current_time >= delay + return_idle)
		{
			enemy_animation = &movement;
			return_idle = current_time;
		}
	}
}