#include "Application.h"
#include "ENEMY_Blue_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
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

	mov_right.PushBack({ 850, 145, 28, 31 });
	mov_right.PushBack({ 888, 145, 25, 31 });
	mov_right.PushBack({ 923, 144, 27, 32 });
	mov_right.PushBack({ 959, 143, 25, 33 });
	mov_right.speed = 0.15f;

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

	mov_up_right.PushBack({ 675, 91, 25, 36 });
	mov_up_right.PushBack({ 711, 94, 26, 34 });
	mov_up_right.PushBack({ 749, 92, 24, 33 });
	mov_up_right.PushBack({ 784, 94, 25, 36 });
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