#include "Application.h"
#include "ENEMY_Basic_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Basic_Robot::ENEMY_Basic_Robot(int x, int y) : Enemy(x, y)
{


	down.PushBack({ 3, 131, 28, 35 });
	left.PushBack({114, 179, 23, 33 });
	right.PushBack({ 162, 132, 24, 35 });
	up.PushBack({ 274, 176, 28, 35 });

	original_position = position;

	enemy_animation = &down;
	
	path.PushBack({ 0.0f, 0.0f }, 300, anim);
	
	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 500000;
	last_time = 0;

}

void ENEMY_Basic_Robot::Move()
{
	
	Focus();

	position = original_position + path.GetCurrentSpeed(&anim);
}

void ENEMY_Basic_Robot::Attack()
{
	current_time = SDL_GetTicks();
	App->particles->enemie_shot.speed.x = -(position.x - App->player->position.x) / 40;
	App->particles->enemie_shot.speed.y = -(position.y - App->player->position.y) / 40;


	if (current_time >= last_time + fire_rate && (-position.y * 2) <= (App->render->camera.y))
	{
		
		App->particles->AddParticle(App->particles->enemie_shot, position.x, position.y, COLLIDER_ENEMY_SHOT, UNDEFINED);
		last_time = current_time;
	}
}

void ENEMY_Basic_Robot::Focus()
{

	if (path.accumulated_speed.IsZero())
	{
		if (App->player->position.x < position.x && App->player->position.y == position.y)
		{
			enemy_animation = &left;
		}
		if (App->player->position.x > position.x + collider->rect.w && App->player->position.y == position.y)
		{
			enemy_animation = &right;
		}
		if (App->player->position.x == position.x && App->player->position.y < position.y)
		{
			enemy_animation = &up;
		}
	}


	
}