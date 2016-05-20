#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ENEMY_Big_Turret_Right.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Big_Turret_Right::ENEMY_Big_Turret_Right(int x, int y) :Enemy(x, y)
{
	//static animations
	idle.PushBack({ 0, 554, 64, 65 });
	hit.PushBack({ 0, 627, 63, 65 });
	enemy_animation = &idle;

	collider = App->collision->AddCollider({ 0, 0, 65, 65 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 400;
	last_time = 0;



	//enemy type
	enemy_type = BIG_TURRET_RIGHT;
}

void ENEMY_Big_Turret_Right::Attack()
{
	current_time = SDL_GetTicks();
	App->particles->enemy_big_shot.speed.x = 2;
	App->particles->enemy_big_shot.speed.y = 1;
	if (current_time >= last_time + fire_rate)
	{
		App->particles->AddParticle(App->particles->enemy_big_shot, position.x + 33, position.y + 42, COLLIDER_ENEMY_SHOT, UNDEFINED);
		last_time = current_time;
	}
}