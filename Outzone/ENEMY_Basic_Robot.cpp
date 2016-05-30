#include "Application.h"
#include "ENEMY_Basic_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include <math.h>
#include <stdlib.h>


#include "SDL\include\SDL_timer.h"

ENEMY_Basic_Robot::ENEMY_Basic_Robot(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
{

	//IDLE animations
	down.PushBack({ 3, 2, 28, 35 });
	left.PushBack({ 114, 50, 23, 33 });
	right.PushBack({ 162, 3, 24, 35 });
	up.PushBack({ 274, 47, 28, 35 });

	midle_down_right.PushBack({ 75, 3, 27, 35 });
	midle_down_right_bot.PushBack({ 38, 3, 29, 34 });
	midle_down_right_top.PushBack({ 111, 1, 26, 35 });

	midle_down_left.PushBack({ 43, 49, 27, 36 });
	midle_down_left_bot.PushBack({ 8, 50, 26, 35 });
	midle_down_left_top.PushBack({ 79, 50, 26, 35 });

	midle_up_right.PushBack({ 239, 2, 25, 35 });
	midle_up_right_bot.PushBack({ 203, 2, 22, 36 });
	midle_up_right_top.PushBack({ 274, 1, 28, 36 });

	midle_up_left.PushBack({ 200, 48, 27, 35 });
	midle_up_left_bot.PushBack({ 161, 50, 24, 35 });
	midle_up_left_top.PushBack({ 239, 48, 26, 35 });

	//MOVEMENT animations
	mov_down.PushBack({ 167, 231, 27, 35 });
	mov_down.PushBack({ 205, 234, 27, 32 });
	mov_down.PushBack({ 243, 233, 28, 33 });
	mov_down.PushBack({ 282, 235, 27, 31 });
	mov_down.speed = 0.15f;

	mov_left.PushBack({ 170, 144, 25, 32 });
	mov_left.PushBack({ 207, 144, 28, 32 });
	mov_left.PushBack({ 244, 143, 25, 33 });
	mov_left.PushBack({ 281, 144, 25, 33 });
	mov_left.speed = 0.15f;

	mov_right.PushBack({ 164, 97, 28, 32 });
	mov_right.PushBack({ 203, 95, 25, 32 });
	mov_right.PushBack({ 240, 96, 27, 32 });
	mov_right.PushBack({ 280, 97, 25, 33 });
	mov_right.speed = 0.15f;

	mov_up.PushBack({ 174, 188, 26, 36 });
	mov_up.PushBack({ 208, 187, 27, 37 });
	mov_up.PushBack({ 243, 189, 26, 35 });
	mov_up.PushBack({ 277, 189, 26, 35 });
	mov_up.speed = 0.15f;

	mov_down_left.PushBack({ 10, 232, 27, 33 });
	mov_down_left.PushBack({ 48, 232, 27, 34 });
	mov_down_left.PushBack({ 84, 231, 25, 34 });
	mov_down_left.PushBack({ 115, 232, 27, 34 });
	mov_down_left.speed = 0.15f;

	mov_down_right.PushBack({ 6, 188, 27, 34 });
	mov_down_right.PushBack({ 41, 189, 26, 33 });
	mov_down_right.PushBack({ 78, 189, 27, 33 });
	mov_down_right.PushBack({ 116, 189, 26, 35 });
	mov_down_right.speed = 0.15f;

	mov_up_left.PushBack({ 6, 144, 26, 35 });
	mov_up_left.PushBack({ 40, 144, 28, 35 });
	mov_up_left.PushBack({ 76, 142, 28, 34 });
	mov_up_left.PushBack({ 115, 142, 27, 33 });
	mov_up_left.speed = 0.15f;

	mov_up_right.PushBack({ 0, 97, 29, 34 });
	mov_up_right.PushBack({ 41, 97, 26, 34 });
	mov_up_right.PushBack({ 80, 97, 24, 33 });
	mov_up_right.PushBack({ 115, 95, 25, 36 });
	mov_up_right.speed = 0.15f;

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
	if (basic_robot_movement == TYPE_DIAGONAL_LEFT)
	{
		path.PushBack({ -0.75f, 0.75f }, 150, anim);
		path.PushBack({ 0.0f, 0.0f }, 100, anim);
		path.PushBack({ -0.75f, 0.75f }, 500, anim);
	}
	if (basic_robot_movement == TYPE_DIAGONAL_LEFT_2)
	{
		path.PushBack({ -0.5f, 0.75f }, 150, anim);
		path.PushBack({ 0.0f, 0.0f }, 100, anim);
		path.PushBack({ -0.5f, 0.75f }, 500, anim);
	}
	if (basic_robot_movement == GET_OUT_CAR_1)
	{
		
		path.PushBack({ 0.8f, 0.0f }, 190, anim);
		path.PushBack({ 0.0f, 0.0f }, 2000, anim);
	}
	if (basic_robot_movement == GET_OUT_CAR_2)
	{
		path.PushBack({ 0.0f, -0.8f }, 50, anim);
		path.PushBack({ 0.8f, 0.0f }, 150, anim);
		path.PushBack({ 0.0f, 0.0f }, 2000, anim);
	}
	if (basic_robot_movement == GET_OUT_CAR_3)
	{
		path.PushBack({ 0.0f, -0.8f }, 50, anim);
		path.PushBack({ 0.8f, 0.0f }, 110, anim);
		path.PushBack({ 0.0f, 0.0f }, 2000, anim);
	}
	if (basic_robot_movement == GET_OUT_CAR_4)
	{
		path.PushBack({ 0.0f, -0.8f }, 50, anim);
		path.PushBack({ 0.8f, 0.0f }, 70, anim);
		path.PushBack({ 0.0f, 0.0f }, 2000, anim);
	}
	if (basic_robot_movement == GET_OUT_CAR_5)
	{
		path.PushBack({ 0.0f, -0.8f }, 50, anim);
		path.PushBack({ 0.8f, 0.0f }, 30, anim);
		path.PushBack({ 0.0f, 0.0f }, 2000, anim);
	}

	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 2000;
	last_time = 0;
	

	//enemy type
	delay = 50;
	live = 2;
	enemy_type = BASIC_ROBOT;
}

void ENEMY_Basic_Robot::Move()
{

	Focus();

	position = original_position + path.GetCurrentSpeed(&anim);

}

void ENEMY_Basic_Robot::Attack()
{
	
	int shot_speed = 3;
	int caos = -20 + rand() % 70;

	current_time = SDL_GetTicks();
	if (current_time >= last_time + fire_rate && (-position.y * 2) <= (App->render->camera.y - 100) && position.x > 0 && position.x < 240)
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
			App->particles->AddParticle(App->particles->enemy_shot, position.x , position.y + 17, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

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
			App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 5 , COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_left_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 8 , position.y - 2, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right_bot)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y + 10, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		if (enemy_animation == &midle_up_right_top)
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 20, position.y - 3, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);

		last_time = current_time;
	}
}

void ENEMY_Basic_Robot::Focus()
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
			if(hit)
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

bool ENEMY_Basic_Robot::Is_Dead()
{
	if (live <= 0)
	{
		App->particles->AddParticle(App->particles->basic_enemy_explosion, position.x, position.y, COLLIDER_NONE, UNDEFINED);
		App->interfice->score += 390;
		return true;
	}
	return false;
}

void ENEMY_Basic_Robot::hitmarker()
{
	hit = true;
}

void ENEMY_Basic_Robot::return_from_hitmarker()
{
	if (current_time >= delay + return_idle)
	{
		hit = false;
		return_idle = current_time;
	}
}