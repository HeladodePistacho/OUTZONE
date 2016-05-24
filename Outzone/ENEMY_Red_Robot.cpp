#include "Application.h"
#include "ENEMY_Red_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Red_Robot::ENEMY_Red_Robot(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
{

	//IDLE animations
	down.PushBack({ 330, 2, 28, 35 });
	left.PushBack({ 453, 46, 23, 33 });
	right.PushBack({ 508, 0, 24, 35 });
	up.PushBack({ 615, 44, 28, 35 });

	midle_down_right.PushBack({ 411, 1, 27, 35 });
	midle_down_right_bot.PushBack({ 370, 2, 27, 35 });
	midle_down_right_top.PushBack({ 450, 1, 26, 35 });

	midle_down_left.PushBack({ 373, 42, 27, 36 });
	midle_down_left_bot.PushBack({ 334, 44, 26, 35 });
	midle_down_left_top.PushBack({ 414, 44, 26, 35 });

	midle_up_right.PushBack({ 578, 1, 25, 35 });
	midle_up_right_bot.PushBack({ 544, 0, 22, 36 });
	midle_up_right_top.PushBack({ 615, 1, 28, 36 });

	midle_up_left.PushBack({ 541, 44, 27, 35 });
	midle_up_left_bot.PushBack({ 506, 44, 24, 35 });
	midle_up_left_top.PushBack({ 579, 44, 26, 35 });

	//MOVEMENT animations
	mov_down.PushBack({ 502, 185, 27, 35 });
	mov_down.PushBack({ 540, 188, 27, 32 });
	mov_down.PushBack({ 581, 187, 28, 33 });
	mov_down.PushBack({ 618, 189, 27, 31 });
	mov_down.speed = 0.15f;

	mov_left.PushBack({ 506, 95, 25, 32 });
	mov_left.PushBack({ 546, 94, 28, 32 });
	mov_left.PushBack({ 581, 94, 25, 33 });
	mov_left.PushBack({ 622, 93, 25, 33 });
	mov_left.speed = 0.15f;

	mov_right.PushBack({ 506, 145, 28, 32 });
	mov_right.PushBack({ 545, 145, 25, 32 });
	mov_right.PushBack({ 585, 145, 27, 32 });
	mov_right.PushBack({ 622, 143, 25, 33 });
	mov_right.speed = 0.15f;

	mov_up.PushBack({ 508, 230, 26, 36 });
	mov_up.PushBack({ 545, 229, 27, 37 });
	mov_up.PushBack({ 581, 229, 26, 35 });
	mov_up.PushBack({ 617, 229, 26, 35 });
	mov_up.speed = 0.15f;

	mov_down_left.PushBack({ 328, 231, 27, 33 });
	mov_down_left.PushBack({ 367, 233, 27, 34 });
	mov_down_left.PushBack({ 411, 231, 25, 34 });
	mov_down_left.PushBack({ 448, 233, 27, 34 });
	mov_down_left.speed = 0.15f;

	mov_down_right.PushBack({ 327, 188, 27, 34 });
	mov_down_right.PushBack({ 365, 187, 26, 33 });
	mov_down_right.PushBack({ 407, 187, 27, 33 });
	mov_down_right.PushBack({ 446, 187, 26, 35 });
	mov_down_right.speed = 0.15f;

	mov_up_left.PushBack({ 329, 141, 26, 35 });
	mov_up_left.PushBack({ 367, 141, 28, 35 });
	mov_up_left.PushBack({ 408, 141, 28, 34 });
	mov_up_left.PushBack({ 450, 142, 27, 33 });
	mov_up_left.speed = 0.15f;

	mov_up_right.PushBack({ 330, 93, 29, 34 });
	mov_up_right.PushBack({ 371, 93, 26, 34 });
	mov_up_right.PushBack({ 415, 94, 24, 33 });
	mov_up_right.PushBack({ 459, 92, 25, 36 });
	mov_up_right.speed = 0.15f;

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
	enemy_type = BASIC_ROBOT;
}

void ENEMY_Red_Robot::Move()
{

	Focus();

	position = original_position + path.GetCurrentSpeed(&anim);

}

void ENEMY_Red_Robot::Attack()
{
	current_time = SDL_GetTicks();
	if (current_time >= last_time + fire_rate && (-position.y * 2) <= (App->render->camera.y))
	{
		App->particles->enemy_shot.speed.x = -(position.x - App->player->position.x) / 40;
		App->particles->enemy_shot.speed.y = -(position.y - App->player->position.y) / 40;

		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);
		last_time = current_time;
	}
}

void ENEMY_Red_Robot::Focus()
{

	if (path.current_speed.IsZero())
	{

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
	else
	{
		if (App->player->position.y < position.y)
		{
			enemy_animation = &mov_up;
			if (App->player->position.x <= position.x - 50) enemy_animation = &mov_up_left;
			if (App->player->position.x >= position.x + 50) enemy_animation = &mov_up_right;

		}

		if (App->player->position.y > position.y)
		{
			enemy_animation = &mov_down;
			if (App->player->position.x <= position.x - 50) enemy_animation = &mov_down_left;
			if (App->player->position.x >= position.x + 50) enemy_animation = &mov_down_right;
		}

		if (App->player->position.x < position.x && App->player->position.y < position.y + 10 && App->player->position.y > position.y - 10)
		{
			enemy_animation = &mov_left;
		}
		if (App->player->position.x > position.x + collider->rect.w && App->player->position.y < position.y + 10 && App->player->position.y > position.y - 10)
		{
			enemy_animation = &mov_right;
		}


	}
}