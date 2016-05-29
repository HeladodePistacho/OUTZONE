#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Big_Turret_Right.h"

#include "SDL\include\SDL_timer.h"
#include <time.h>
#include <stdlib.h>

ENEMY_Big_Turret_Right::ENEMY_Big_Turret_Right(int x, int y) :Enemy(x, y)
{
	//static animations
	idle.PushBack({ 0, 554, 64, 65 });
	hit.PushBack({ 0, 627, 63, 65 });
	enemy_animation = &idle;

	collider = App->collision->AddCollider({ 0, 0, 65, 65 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 300;
	last_time = 0;

	delay = 150;


	//enemy type
	live = 16;
	enemy_type = BIG_TURRET_RIGHT;
}

void ENEMY_Big_Turret_Right::Attack()
{
	current_time = SDL_GetTicks();

	if (current_time >= last_time + fire_rate)
	{
		if (App->particles->enemy_big_shot.speed.x == 2 && App->particles->enemy_big_shot.speed.y == 2 && direction == LEFT){
			App->particles->enemy_big_shot.speed.x = 1;
			App->particles->enemy_big_shot.speed.y = 2;
			direction = RIGHT;
		}
		else if (App->particles->enemy_big_shot.speed.x == 2 && App->particles->enemy_big_shot.speed.y == 2 && direction == RIGHT ){
			App->particles->enemy_big_shot.speed.x = 2;
			App->particles->enemy_big_shot.speed.y = 1;
			direction = LEFT;
		}
		else{
			App->particles->enemy_big_shot.speed.x = 2;
			App->particles->enemy_big_shot.speed.y = 2;
		}
		App->particles->AddParticle(App->particles->enemy_big_shot, position.x + 33, position.y + 42, COLLIDER_ENEMY_SHOT, ENEMY_BIG_SHOT);
		last_time = current_time;
	}
}

bool ENEMY_Big_Turret_Right::Is_Dead()
{
	if (live <= 0)
	{
		App->particles->AddParticle(App->particles->big_enemy_explosion, position.x - 40, position.y - 40, COLLIDER_NONE, UNDEFINED);
		App->particles->AddParticle(App->particles->big_turret_fire, position.x, position.y, COLLIDER_NONE, UNDEFINED);
		App->interfice->score += 810;
		return true;
	}
	return false;
}

void ENEMY_Big_Turret_Right::hitmarker()
{
	if (enemy_animation != &hit)
		enemy_animation = &hit;
}

void ENEMY_Big_Turret_Right::return_from_hitmarker()
{
	if (enemy_animation != &idle)
	{
		if (current_time >= delay + return_idle)
		{
			enemy_animation = &idle;
			return_idle = current_time;
		}
	}
}