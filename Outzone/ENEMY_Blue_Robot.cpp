#include "Application.h"
#include "ENEMY_Blue_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include <stdlib.h>
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Blue_Robot::ENEMY_Blue_Robot(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
{

	//IDLE animations
	down.PushBack({ 674, 4, 28, 34 });
	left.PushBack({ 785, 48, 23, 33 });
	right.PushBack({ 850, 6, 28, 31 });
	up.PushBack({ 958, 46, 27, 36 });

	midle_down_right.PushBack({ 782, 1, 26, 35 });
	midle_down_right_bot.PushBack({ 713, 3, 29, 33 });
	midle_down_right_top.PushBack({ 749, 0, 27, 35 });

	midle_down_left.PushBack({ 713, 47, 27, 35 });
	midle_down_left_bot.PushBack({ 675, 43, 27, 34 });
	midle_down_left_top.PushBack({ 750, 47, 26, 35 });

	midle_up_right.PushBack({ 921, 4, 25, 34 });
	midle_up_right_bot.PushBack({ 888, 4, 22, 35 });
	midle_up_right_top.PushBack({ 921, 4, 25, 34 });

	midle_up_left.PushBack({ 885, 47, 28, 35 });
	midle_up_left_bot.PushBack({ 885, 47, 28, 35 });
	midle_up_left_top.PushBack({ 885, 47, 28, 35 });

	//MOVEMENT animations
	mov_down.PushBack({ 848, 186, 27, 35 });
	mov_down.PushBack({ 884, 189, 27, 32 });
	mov_down.PushBack({ 921, 188, 28, 33 });
	mov_down.PushBack({ 960, 190, 27, 31 });
	mov_down.speed = 0.15f;

	mov_left.PushBack({ 850, 96, 25, 33 });
	mov_left.PushBack({ 889, 95, 25, 33 });
	mov_left.PushBack({ 926, 96, 25, 32 });
	mov_left.PushBack({ 959, 94, 28, 33 });
	mov_left.speed = 0.15f;

	mov_right.PushBack({ 850, 145, 28, 32 });
	mov_right.PushBack({ 888, 145, 25, 32 });
	mov_right.PushBack({ 923, 144, 27, 33 });
	mov_right.PushBack({ 959, 143, 25, 34 });
	mov_right.speed = 0.17f;

	mov_up.PushBack({ 851, 228, 26, 36 });
	mov_up.PushBack({ 888, 227, 27, 37 });
	mov_up.PushBack({ 926, 228, 26, 35 });
	mov_up.PushBack({ 959, 228, 26, 35 });
	mov_up.speed = 0.15f;

	mov_down_left.PushBack({ 675, 229, 27, 33 });
	mov_down_left.PushBack({ 713, 229, 27, 34 });
	mov_down_left.PushBack({ 750, 229, 25, 34 });
	mov_down_left.PushBack({ 782, 229, 27, 34 });
	mov_down_left.speed = 0.15f;

	mov_down_right.PushBack({ 672, 185, 27, 34 });
	mov_down_right.PushBack({ 707, 186, 26, 33 });
	mov_down_right.PushBack({ 744, 186, 27, 33 });
	mov_down_right.PushBack({ 782, 186, 26, 35 });
	mov_down_right.speed = 0.15f;

	mov_up_left.PushBack({ 673, 141, 27, 35 });
	mov_up_left.PushBack({ 709, 141, 27, 35 });
	mov_up_left.PushBack({ 746, 144, 28, 32 });
	mov_up_left.PushBack({ 782, 144, 28, 32 });
	mov_up_left.speed = 0.15f;

	mov_up_right.PushBack({ 784, 94, 24, 34 });
	mov_up_right.PushBack({ 675, 91, 25, 36 });
	mov_up_right.PushBack({ 711, 94, 29, 34 });
	mov_up_right.PushBack({ 749, 92, 26, 35 });
	mov_up_right.speed = 0.17f;

	hit_down.PushBack({ 1021, 3, 28, 35 });
	hit_left.PushBack({ 1144, 47, 23, 33 });
	hit_right.PushBack({ 1199, 1, 24, 35 });
	hit_up.PushBack({ 1306, 45, 28, 35 });

	hit_midle_down_right.PushBack({ 1102, 2, 27, 35 });
	hit_midle_down_right_bot.PushBack({ 1061, 3, 29, 34 });
	hit_midle_down_right_top.PushBack({ 1141, 2, 26, 35 });

	hit_midle_down_left.PushBack({ 1066, 43, 27, 36 });
	hit_midle_down_left_bot.PushBack({ 1025, 45, 26, 35 });
	hit_midle_down_left_top.PushBack({ 1105, 45, 26, 35 });

	hit_midle_up_right.PushBack({ 1269, 2, 25, 35 });
	hit_midle_up_right_bot.PushBack({ 1235, 1, 22, 36 });
	hit_midle_up_right_top.PushBack({ 1306, 2, 28, 36 });

	hit_midle_up_left.PushBack({ 1232, 45, 27, 35 });
	hit_midle_up_left_bot.PushBack({ 1197, 45, 24, 35 });
	hit_midle_up_left_top.PushBack({ 1270, 45, 26, 35 });

	original_position = position;

	enemy_animation = &down;

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
	delay = 150;
	live = 2;
	enemy_type = BLUE_ROBOT;
}

void ENEMY_Blue_Robot::Move()
{

	Focus();

	position = original_position + path.GetCurrentSpeed(&anim);

}

void ENEMY_Blue_Robot::Attack()
{

	int shot_speed = 3;
	int caos = -20 + rand() % 70;

	current_time = SDL_GetTicks();
	if (current_time >= last_time + fire_rate && (-position.y * 2) <= (App->render->camera.y) && position.x > 0 && position.x < 240)
	{
		//find angle
		float angle = atan2((position.y - App->player->position.y), (position.x - App->player->position.x - caos));
		App->particles->enemy_shot.speed.x = -cos(angle) * shot_speed;
		App->particles->enemy_shot.speed.y = -sin(angle) * shot_speed;

		if (enemy_animation == &down || enemy_animation == &mov_down)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 10, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &up || enemy_animation == &mov_up)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 12, position.y - 1, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &left || enemy_animation == &mov_left)
			App->particles->AddParticle(App->particles->enemy_shot, position.x - 2, position.y + 10, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &right || enemy_animation == &mov_right)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y + 12, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_left || enemy_animation == &mov_down_left)
			App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 17, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_right || enemy_animation == &mov_down_right)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left || enemy_animation == &mov_up_left)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 3, position.y, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right || enemy_animation == &mov_up_right)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y + 5, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_left_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 5, position.y + 22, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_left_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_right_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 17, position.y + 22, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_down_right_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 23, position.y + 20, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 5, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 8, position.y - 2, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y + 10, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y - 3, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		last_time = current_time;
	}
}

void ENEMY_Blue_Robot::Focus()
{
		if (path.current_speed.IsZero())
		{

			if (App->player->position.y < position.y)
			{
				if (hit)
					enemy_animation = &hit_up;
				else enemy_animation = &up;

				if (position.x > App->player->position.x)
				{
					if (App->player->position.x > position.x - 50 && App->player->position.x < position.x)
					{
						if (hit)
							enemy_animation = &hit_midle_up_left_top;
						else enemy_animation = &midle_up_left_top;
					}
					if (App->player->position.x > position.x - 100 && App->player->position.x <= position.x - 50)
					{
						if (hit)
							enemy_animation = &hit_midle_up_left;
						else enemy_animation = &midle_up_left;
					}
					if (App->player->position.x >= -2 && App->player->position.x <= position.x - 100)
					{
						if (hit)
							enemy_animation = &hit_midle_up_left_bot;
						else enemy_animation = &midle_up_left_bot;
					}
				}


				if (position.x < App->player->position.x)
				{
					if (App->player->position.x > position.x + 50 && App->player->position.x < position.x + 100)
					{
						if (hit)
							enemy_animation = &hit_midle_up_right_top;
						else enemy_animation = &midle_up_right_top;
					}
					if (App->player->position.x >= position.x + 100 && App->player->position.x < position.x + 120)
					{
						if (hit)
							enemy_animation = &hit_midle_up_right;
						else enemy_animation = &midle_up_right;
					}
					if (App->player->position.x >= position.x + 120)
					{
						if (hit)
							enemy_animation = &hit_midle_up_right_bot;
						else enemy_animation = &midle_up_right_bot;
					}
				}
			}
			if (App->player->position.y > position.y)
			{
				if (hit)
					enemy_animation = &hit_down;
				else enemy_animation = &down;

				if (position.x > App->player->position.x)
				{
					if (App->player->position.x > position.x - 50 && App->player->position.x < position.x)
					{
						if (hit)
							enemy_animation = &hit_midle_down_left_bot;
						else enemy_animation = &midle_down_left_bot;
					}
					if (App->player->position.x > position.x - 100 && App->player->position.x <= position.x - 50)
					{
						if (hit)
							enemy_animation = &hit_midle_down_left;
						else enemy_animation = &midle_down_left;
					}
					if (App->player->position.x >= -2 && App->player->position.x <= position.x - 100)
					{
						if (hit)
							enemy_animation = &hit_midle_down_left_top;
						else enemy_animation = &midle_down_left_top;
					}
				}

				if (position.x < App->player->position.x)
				{
					if (App->player->position.x > position.x + 50 && App->player->position.x < position.x + 100)
					{
						if (hit)
							enemy_animation = &hit_midle_down_right_bot;
						else enemy_animation = &midle_down_right_bot;
					}
					if (App->player->position.x >= position.x + 100 && App->player->position.x < position.x + 120)
					{
						if (hit)
							enemy_animation = &hit_midle_down_right;
						else enemy_animation = &midle_down_right;
					}
					if (App->player->position.x >= position.x + 120)
					{
						if (hit)
							enemy_animation = &hit_midle_down_right_top;
						else enemy_animation = &midle_down_right_top;
					}
				}

			}
			if (App->player->position.x < position.x && App->player->position.y < position.y + 5 && App->player->position.y > position.y - 5)
			{
				if (hit)
					enemy_animation = &hit_left;
				else enemy_animation = &left;
			}
			if (App->player->position.x > position.x + collider->rect.w && App->player->position.y < position.y + 5 && App->player->position.y > position.y - 5)
			{
				if (hit)
					enemy_animation = &hit_right;
				else enemy_animation = &right;
			}
		}
		else
		{
			if (App->player->position.y < position.y)
			{
				if (hit)
					enemy_animation = &hit_up;
				else enemy_animation = &mov_up;
				if (App->player->position.x <= position.x - 50)
				{
					if (hit)
						enemy_animation = &hit_midle_up_left;
					else enemy_animation = &mov_up_left;
				}
				if (App->player->position.x >= position.x + 50)
				{
					if (hit)
						enemy_animation = &hit_midle_up_right;
					else enemy_animation = &mov_up_right;
				}

			}

			if (App->player->position.y > position.y)
			{
				if (hit)
					enemy_animation = &hit_down;
				else enemy_animation = &mov_down;
				if (App->player->position.x <= position.x - 50)
				{
					if (hit)
						enemy_animation = &hit_midle_down_left;
					else enemy_animation = &mov_down_left;
				}
				if (App->player->position.x >= position.x + 50)
				{
					if (hit)
						enemy_animation = &hit_midle_up_right;
					else enemy_animation = &mov_down_right;
				}
			}

			if (App->player->position.x < position.x && App->player->position.y < position.y + 10 && App->player->position.y > position.y - 10)
			{
				if (hit)
					enemy_animation = &hit_left;
				else enemy_animation = &mov_left;
			}
			if (App->player->position.x > position.x + collider->rect.w && App->player->position.y < position.y + 10 && App->player->position.y > position.y - 10)
			{
				if (hit)
					enemy_animation = &hit_right;
				else enemy_animation = &mov_right;
			}
		}
	
}

bool ENEMY_Blue_Robot::Is_Dead()
{
	if (live <= 0)
	{
		App->particles->AddParticle(App->particles->basic_enemy_explosion, position.x, position.y, COLLIDER_NONE, UNDEFINED);
		App->interfice->score += 390;
		return true;
	}
	return false;
}

void ENEMY_Blue_Robot::hitmarker()
{
	hit = true;
}

void ENEMY_Blue_Robot::return_from_hitmarker()
{
	if (current_time >= delay + return_idle)
	{
		hit = false;
		return_idle = current_time;
	}
}