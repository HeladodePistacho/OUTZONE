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
	movement.PushBack({ 0, 760, 44, 41 });
	movement.PushBack({ 52, 760, 46, 47 });
	movement.PushBack({ 0, 760, 44, 41 });
	movement.PushBack({ 52, 760, 46, 47 });
	movement.PushBack({ 0, 760, 44, 41 });
	movement.PushBack({ 52, 760, 46, 47 });
	movement.PushBack({ 0, 760, 44, 41 });
	movement.PushBack({ 52, 760, 46, 47 });
	movement.PushBack({ 106, 760, 46, 47 });
	movement.PushBack({ 163, 760, 45, 46 });
	movement.PushBack({ 219, 760, 46, 47 });

	movement.speed = 0.32f;

	

	enemy_animation = &movement;

	original_position = position;

	//Path1
	if (basic_robot_movement == TYPE_SEMI_CIRCLE)
	{
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
	}
		
	//Path2
	if (basic_robot_movement == TYPE_CIRCLE)
	{
		path.PushBack({ 2.0f, 0.0f }, 45, anim);
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
	}

	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 700;
	last_time = fire_rate;


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
	
	current_time = SDL_GetTicks();

	if (current_time >= last_time + fire_rate)
	{
		App->particles->AddParticle(App->particles->missile_impact, position.x + 10, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_MISSILE);
		App->particles->AddParticle(App->particles->enemy_missile, position.x + 10, position.y + 15, COLLIDER_ENEMY_SHOT, ENEMY_MISSILE);
		last_time = current_time;
	}

}
