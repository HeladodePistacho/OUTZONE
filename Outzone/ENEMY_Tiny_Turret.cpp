#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Tiny_Turret.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Tiny_Turret::ENEMY_Tiny_Turret(int x, int y) :Enemy(x, y)
{
	//static animations
	down.PushBack({ 342, 488, 29, 45 });
	left.PushBack({ 154, 433, 30, 43 });
	right.PushBack({ 161, 490, 28, 43 });
	up.PushBack({ 339, 429, 27, 47 });
	midle_down_right.PushBack({ 252, 489, 28, 44 });
	midle_down_right_bot.PushBack({ 298, 488, 28, 45 });
	midle_down_right_top.PushBack({ 207, 489, 27, 44 });
	midle_down_left.PushBack({ 68, 433, 26, 44 });
	midle_down_left_bot.PushBack({ 22, 432, 27, 45 });
	midle_down_left_top.PushBack({ 111, 432, 29, 44 });
	midle_up_right.PushBack({ 69, 488, 27, 45 });
	midle_up_right_bot.PushBack({ 116, 490, 27, 43 });
	midle_up_right_top.PushBack({ 22, 487, 26, 46 });
	midle_up_left.PushBack({ 251, 431, 24, 45 });
	midle_up_left_bot.PushBack({ 203, 433, 28, 43 });
	midle_up_left_top.PushBack({ 296, 430, 24, 46 });

	enemy_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 30, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 10000;
	last_time = 0;

	current_time = SDL_GetTicks();

	//enemy type
	enemy_type = TINY_TURRET;
}

void ENEMY_Tiny_Turret::Attack()
{
	if (current_time >= last_time + fire_rate && (-position.y * 2) <= (App->render->camera.y))
	{
		App->particles->enemy_shot.speed.x = -(position.x - App->player->position.x) / 40;
		App->particles->enemy_shot.speed.y = -(position.y - App->player->position.y) / 40; 
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);
		last_time = current_time;
	}
}

void ENEMY_Tiny_Turret::Move()
{
	Focus();
}

void ENEMY_Tiny_Turret::Focus(){

	if (App->player->position.y < position.y)
	{
		enemy_animation = &up;

		if (position.x > App->player->position.x)
		{
			if (App->player->position.x > position.x - 50 && App->player->position.x < position.x)
			{
				enemy_animation = &midle_up_left_top;
			}
			if (App->player->position.x > position.x - 100 && App->player->position.x <= position.x - 50)
			{
				enemy_animation = &midle_up_left;
			}
			if (App->player->position.x >= -2 && App->player->position.x <= position.x - 100)
			{
				enemy_animation = &midle_up_left_bot;
			}
		}


		if (position.x < App->player->position.x)
		{
			if (App->player->position.x > position.x + 50 && App->player->position.x < position.x + 100)
			{
				enemy_animation = &midle_up_right_top;
			}
			if (App->player->position.x >= position.x + 100 && App->player->position.x < position.x + 120)
			{
				enemy_animation = &midle_up_right;
			}
			if (App->player->position.x >= position.x + 120)
			{
				enemy_animation = &midle_up_right_bot;
			}
		}
	}
	if (App->player->position.y > position.y)
	{
		enemy_animation = &down;

		if (position.x > App->player->position.x)
		{
			if (App->player->position.x > position.x - 50 && App->player->position.x < position.x)
			{
				enemy_animation = &midle_down_left_bot;
			}
			if (App->player->position.x > position.x - 100 && App->player->position.x <= position.x - 50)
			{
				enemy_animation = &midle_down_left;
			}
			if (App->player->position.x >= -2 && App->player->position.x <= position.x - 100)
			{
				enemy_animation = &midle_down_left_top;
			}
		}

		if (position.x < App->player->position.x)
		{
			if (App->player->position.x > position.x + 50 && App->player->position.x < position.x + 100)
			{
				enemy_animation = &midle_down_right_bot;
			}
			if (App->player->position.x >= position.x + 100 && App->player->position.x < position.x + 120)
			{
				enemy_animation = &midle_down_right;
			}
			if (App->player->position.x >= position.x + 120)
			{
				enemy_animation = &midle_down_right_top;
			}
		}

	}
	if (App->player->position.x < position.x && App->player->position.y < position.y + 5 && App->player->position.y > position.y - 5)
	{
		enemy_animation = &left;
	}
	if (App->player->position.x > position.x + collider->rect.w && App->player->position.y < position.y + 5 && App->player->position.y > position.y - 5)
	{
		enemy_animation = &right;
	}
}