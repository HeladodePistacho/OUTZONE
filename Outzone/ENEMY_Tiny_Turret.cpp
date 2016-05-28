#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Tiny_Turret.h"
#include <stdlib.h>

#include "SDL\include\SDL_timer.h"

ENEMY_Tiny_Turret::ENEMY_Tiny_Turret(int x, int y) :Enemy(x, y)
{
	//static animations
	down.PushBack({ 341, 485, 33, 48 });
	left.PushBack({ 156, 428, 31, 48 });
	right.PushBack({ 159, 485, 33, 48 });
	up.PushBack({ 337, 428, 33, 48 });

	midle_down_right.PushBack({ 251, 485, 33, 48 });
	midle_down_right_bot.PushBack({ 294, 485, 33, 48 });
	midle_down_right_top.PushBack({ 205, 485, 33, 48 });

	midle_down_left.PushBack({ 65, 429, 33, 48 });
	midle_down_left_bot.PushBack({ 20, 429, 33, 48 });
	midle_down_left_top.PushBack({ 112, 428, 34, 47 });

	midle_up_right.PushBack({ 67, 485, 33, 48 });
	midle_up_right_bot.PushBack({ 113, 485, 33, 48});
	midle_up_right_top.PushBack({ 20, 485, 33, 48 });

	midle_up_left.PushBack({ 248, 428, 33, 48 });
	midle_up_left_bot.PushBack({ 203, 428, 33, 47 });
	midle_up_left_top.PushBack({ 293, 428, 33, 48 });

	enemy_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 30, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 2000;
	last_time = 0;

	current_time = SDL_GetTicks();

	//enemy type
	live = 4;
	enemy_type = TINY_TURRET;
}

void ENEMY_Tiny_Turret::Attack()
{
	int shot_speed = 3;
	int caos = -20 + rand() % 70;

	current_time = SDL_GetTicks();
	{
		//find angle
		float angle = atan2((position.y - App->player->position.y), (position.x - App->player->position.x - caos));
		App->particles->enemy_shot.speed.x = -cos(angle) * shot_speed;
		App->particles->enemy_shot.speed.y = -sin(angle) * shot_speed;

		if (enemy_animation == &down)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 10, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &up)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 12, position.y - 1, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &left)
			App->particles->AddParticle(App->particles->enemy_shot, position.x - 2, position.y + 10, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &right)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 25, position.y + 12, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_left)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 5, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_right)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 3, position.y, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_left_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 5, position.y + 25, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_left_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x - 2, position.y + 17, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_right_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 17, position.y + 22, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_right_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 25, position.y + 16, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 5, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 8, position.y - 2, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 27, position.y + 5, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y - 3, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

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