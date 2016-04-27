#include "Application.h"
#include "ENEMY_Basic_Robot.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL\include\SDL_timer.h"

ENEMY_Basic_Robot::ENEMY_Basic_Robot(int x, int y) : Enemy(x, y)
{


	walk.PushBack({ 109, 176, 27, 32 });

	original_position = position;

	path.PushBack({ 0.0f, 0.0f }, 150, &walk);
	
	
	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire_rate = 2000;
	last_time = 0;

}

void ENEMY_Basic_Robot::Move()
{

	position = original_position + path.GetCurrentSpeed(&animation);
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

