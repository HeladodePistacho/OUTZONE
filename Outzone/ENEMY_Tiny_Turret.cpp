#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Tiny_Turret.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Tiny_Turret::ENEMY_Tiny_Turret(int x, int y) :Enemy(x, y)
{
	//static animations
	down.PushBack({ 319, 487, 31, 48 });
	left.PushBack({ 131, 433, 32, 45 });
	right.PushBack({ 137, 498, 31, 46 });
	up.PushBack({ 317, 429, 27, 48 });
	midle_down_right.PushBack({ 229, 490, 30, 45 });
	midle_down_right_bot.PushBack({ 272, 489, 30, 46 });
	midle_down_right_top.PushBack({ 185, 490, 28, 45 });
	midle_down_left.PushBack({ 46, 434, 27, 45 });
	midle_down_left_bot.PushBack({ 0, 432, 28, 47 });
	midle_down_left_top.PushBack({ 89, 432, 30, 46 });
	midle_up_right.PushBack({ 47, 65, 452, 46 });
	midle_up_right_bot.PushBack({ 93, 490, 29, 45 });
	midle_up_right_top.PushBack({ 0, 488, 27, 47 });
	midle_up_left.PushBack({ 228, 7, 450, 47 });
	midle_up_left_bot.PushBack({ 180, 434, 30, 44 });
	midle_up_left_top.PushBack({ 173, 431, 26, 47 });

	enemy_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 30, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 10000;
	last_time = 0;

	current_time = SDL_GetTicks();
}

void ENEMY_Tiny_Turret::Attack()
{
	App->particles->enemy_shot.speed.x = -(position.x - App->player->position.x) / 40;
	App->particles->enemy_shot.speed.y = -(position.y - App->player->position.y) / 40;


	if (current_time >= last_time + fire_rate && (-position.y * 2) <= (App->render->camera.y))
	{

		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, COLLIDER_ENEMY_SHOT, UNDEFINED);
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