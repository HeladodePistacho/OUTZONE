#include "Application.h"
#include "ENEMY_Basic_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Basic_Robot::ENEMY_Basic_Robot(int x, int y) : Enemy(x, y)
{

	//IDLE animations
	down.PushBack({ 3, 131, 28, 35 });
	left.PushBack({114, 179, 23, 33 });
	right.PushBack({ 162, 132, 24, 35 });
	up.PushBack({ 274, 176, 28, 35 });

	midle_down_right.PushBack({ 75, 132, 27, 35 });
	midle_down_right_bot.PushBack({ 38, 132, 29, 34 });
	midle_down_right_top.PushBack({ 111, 130, 26, 35 });

	midle_down_left.PushBack({ 43, 178, 27, 36 });
	midle_down_left_bot.PushBack({ 8, 179, 26, 35 });
	midle_down_left_top.PushBack({ 79, 179, 26, 35 });

	midle_up_right.PushBack({ 239, 131, 25, 35 });
	midle_up_right_bot.PushBack({ 203, 131, 22, 36 });
	midle_up_right_top.PushBack({ 274, 130, 28, 36 });

	midle_up_left.PushBack({ 200, 177, 27, 35 });
	midle_up_left_bot.PushBack({ 161, 179, 24, 35 });
	midle_up_left_top.PushBack({ 239, 177, 26, 35 });

	//MOVEMENT animations
	mov_down.PushBack({ 167, 360, 27, 35 });
	mov_down.PushBack({ 205, 363, 27, 32 });
	mov_down.PushBack({ 243, 362, 28, 33 });
	mov_down.PushBack({ 282, 364, 27, 31 });
	mov_down.speed = 0.15f;

	mov_left.PushBack({ 170, 273, 25, 32 });
	mov_left.PushBack({ 207, 273, 28, 32 });
	mov_left.PushBack({ 244, 272, 25, 33 });
	mov_left.PushBack({ 281, 273, 25, 33 });
	mov_left.speed = 0.15f;

	mov_right.PushBack({ 164, 226, 28, 32 });
	mov_right.PushBack({ 203, 224, 25, 32 });
	mov_right.PushBack({ 240, 225, 27, 32 });
	mov_right.PushBack({ 280, 224, 25, 33 });
	mov_right.speed = 0.15f;

	mov_up.PushBack({ 174, 317, 26, 36 });
	mov_up.PushBack({ 208, 316, 27, 37 });
	mov_up.PushBack({ 243, 318, 26, 35 });
	mov_up.PushBack({ 277, 318, 26, 35 });
	mov_up.speed = 0.15f;

	mov_down_left.PushBack({ 10, 361, 27, 33 });
	mov_down_left.PushBack({ 48, 361, 27, 34 });
	mov_down_left.PushBack({ 84, 360, 25, 34 });
	mov_down_left.PushBack({ 115, 361, 27, 34 });
	mov_down_left.speed = 0.15f;

	mov_down_right.PushBack({ 6, 317, 27, 34});
	mov_down_right.PushBack({ 41, 318, 26, 33});
	mov_down_right.PushBack({ 78, 318, 27, 33});
	mov_down_right.PushBack({ 116, 318, 26, 35});
	mov_down_right.speed = 0.15f;

	mov_up_left.PushBack({ 6, 273, 26, 35});
	mov_up_left.PushBack({ 40, 273, 28, 35});
	mov_up_left.PushBack({ 76, 271, 28, 34});
	mov_up_left.PushBack({ 115, 271, 27, 33});
	mov_up_left.speed = 0.15f;

	mov_up_right.PushBack({ 0, 226, 29, 34});
	mov_up_right.PushBack({ 41, 226, 26, 34});
	mov_up_right.PushBack({ 80, 226, 24, 33});
	mov_up_right.PushBack({ 115, 224, 25, 36});
	mov_up_right.speed = 0.15f;

	original_position = position;

	enemy_animation = &down;
	
	path.PushBack({ 0.0f, 0.0f }, 300, anim);
	path.PushBack({ 0.0f, 0.6f }, 150, anim);
	

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
			if (App->player->position.x <= position.x - 20) enemy_animation = &mov_up_left;
			if (App->player->position.x >= position.x + 20) enemy_animation = &mov_up_right;

		}
		
		if (App->player->position.y > position.y)
		{
			enemy_animation = &mov_down;
			if (App->player->position.x <= position.x - 20) enemy_animation = &mov_down_left;
			if (App->player->position.x >= position.x + 20) enemy_animation = &mov_down_right;
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