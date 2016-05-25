#include "Application.h"
#include "ENEMY_Blue_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Blue_Robot::ENEMY_Blue_Robot(int x, int y, MOVEMENT_TYPES type) : Enemy(x, y), basic_robot_movement(type)
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
	live = 2;
	enemy_type = BASIC_ROBOT;
}

void ENEMY_Blue_Robot::Move()
{

	Focus();

	position = original_position + path.GetCurrentSpeed(&anim);

}

void ENEMY_Blue_Robot::Attack()
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

void ENEMY_Blue_Robot::Focus()
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