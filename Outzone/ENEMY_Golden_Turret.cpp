#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Golden_Turret.h"

#include "SDL\include\SDL_timer.h"
#include <time.h>
#include <stdlib.h>

ENEMY_Golden_Turret::ENEMY_Golden_Turret(int x, int y) :Enemy(x, y)
{
	//static animations
	idle.PushBack({ 0, 704, 26, 40 });
	idle.PushBack({ 29, 704, 26, 40 });
	idle.loop = true;
	idle.speed = 0.2f;
	hit.PushBack({ 58, 704, 26, 40 });
	enemy_animation = &idle;

	collider = App->collision->AddCollider({ 0, 0, 26, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 350;
	last_time = 0;


	delay = 180;
	

	//enemy type
	live = 8;
	enemy_type = GOLDEN_TURRET;
}

void ENEMY_Golden_Turret::Attack()
{

	current_time = SDL_GetTicks();



	if (current_time >= last_time + fire_rate)
	{
		if (bullet_speed.x == -3 && bullet_speed.y == 1){
			direction = RIGHT;
			bullet_speed.x = -2;
			bullet_speed.y = 2;
		
		}
		else if (bullet_speed.x == 3 && bullet_speed.y == 1){
			direction = LEFT;
			bullet_speed.x = 2;
			bullet_speed.y = 2;
		}
		else if (bullet_speed.x == 0 && bullet_speed.y == 2){
			if (direction == LEFT){
				bullet_speed.x = -1;
				bullet_speed.y = 2;
			}
			if (direction == RIGHT){
				bullet_speed.x = 1;
				bullet_speed.y = 2;
			
			}
		}
		else if (bullet_speed.x == -2 && bullet_speed.y == 2){
			if (direction == LEFT){
				bullet_speed.x = -3;
				bullet_speed.y = 1;
				
			}
			if (direction == RIGHT) {
				bullet_speed.x = -1;
				bullet_speed.y = 2;
			}
		}
		else if (bullet_speed.x == -1 && bullet_speed.y == 2){
			if (direction == LEFT){
				bullet_speed.x = -2;
				bullet_speed.y = 2;
			}
			if (direction == RIGHT) {
				bullet_speed.x = 0;
				bullet_speed.y = 2;
			}
		}
		else if (bullet_speed.x == 2 && bullet_speed.y == 2){
			if (direction == LEFT){
				bullet_speed.x = 1;
				bullet_speed.y = 2;
			}
			if (direction == RIGHT) {
				bullet_speed.x = 3;
				bullet_speed.y = 1;
			}
		}
		else if (bullet_speed.x == 1 && bullet_speed.y == 2){
			if (direction == LEFT){
				bullet_speed.x = 0;
				bullet_speed.y = 2;
			}
			if (direction == RIGHT) {
				bullet_speed.x = 2;
				bullet_speed.y = 2;
			}
		}
		else{
			bullet_speed.x = 0;
			bullet_speed.y = 2;
			
		}

		App->particles->enemy_shot.speed.x = bullet_speed.x;
		App->particles->enemy_shot.speed.y = bullet_speed.y;
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 10, position.y + 16, COLLIDER_ENEMY_SHOT, ENEMY_SHOT);
		last_time = current_time;
	}
}

bool ENEMY_Golden_Turret::Is_Dead()
{
	if (live <= 0)
	{
		App->particles->AddParticle(App->particles->basic_enemy_explosion, position.x - 10, position.y - 2, COLLIDER_NONE, UNDEFINED);
		App->interfice->score += 290;
		App->interfice->enemies_def_count++;
		return true;
	}
	return false;
}

void ENEMY_Golden_Turret::hitmarker()
{
	if (enemy_animation != &hit)
		enemy_animation = &hit;
		
}

void ENEMY_Golden_Turret::return_from_hitmarker()
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