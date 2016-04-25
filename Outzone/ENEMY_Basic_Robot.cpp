#include "Application.h"
#include "ENEMY_Basic_Robot.h"
#include "ModuleCollision.h"

ENEMY_Basic_Robot::ENEMY_Basic_Robot(int x, int y) : Enemy(x, y)
{

	walk.PushBack({ 109, 176, 27, 32 });

	original_position = position;

	path.PushBack({ 0.0f, 0.0f }, 100, &walk);
	
	collider = App->collision->AddCollider({ 0, 0, 27, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void ENEMY_Basic_Robot::Move()
{

	position = original_position + path.GetCurrentSpeed(&animation);
}
