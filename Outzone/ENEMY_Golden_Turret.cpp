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
	idle.PushBack({ 0, 703, 27, 42 });
	idle.PushBack({ 29, 703, 28, 42 });
	idle.loop = true;
	idle.speed = 0.1f;
	hit.PushBack({ 57, 703, 28, 41 });
	enemy_animation = &idle;

	collider = App->collision->AddCollider({ 0, 0, 30, 35 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 100;
	last_time = 0;



	//enemy type
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