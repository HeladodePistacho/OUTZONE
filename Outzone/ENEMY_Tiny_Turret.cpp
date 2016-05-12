#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Tiny_Turret.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Tiny_Turret::ENEMY_Tiny_Turret(int x, int y) :Enemy(x, y)
{
	//static animations
	down.PushBack({ 333, 63, 31, 48 });
	left.PushBack({ 145, 9, 32, 45 });
	right.PushBack({ 151, 65, 31, 46 });
	up.PushBack({ 331, 5, 27, 48 });
	midle_down_right.PushBack({ 243, 66, 30, 45 });
	midle_down_right_bot.PushBack({ 286, 65, 30, 46 });
	midle_down_right_top.PushBack({ 199, 66, 28, 45 });
	midle_down_left.PushBack({ 60, 10, 27, 45 });
	midle_down_left_bot.PushBack({ 14, 8, 28, 47 });
	midle_down_left_top.PushBack({ 103, 8, 30, 46 });
	midle_up_right.PushBack({ 61, 65, 28, 46 });
	midle_up_right_bot.PushBack({ 107, 66, 29, 45 });
	midle_up_right_top.PushBack({ 14, 64, 27, 47 });
	midle_up_left.PushBack({ 242, 7, 26, 47 });
	midle_up_left_bot.PushBack({ 194, 10, 30, 44 });
	midle_up_left_top.PushBack({ 287, 7, 26, 47 });

	enemy_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 20, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 1000;
	last_time = 0;
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