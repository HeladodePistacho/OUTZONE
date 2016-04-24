#include "Application.h"
#include "ModuleTextures.h"
#include "Module_lvl_1.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleChangeScene.h"
#include "ModuleParticles.h"
ModulePlayer::ModulePlayer()
{

	//AFK
	idle.PushBack({ 2, 156, 29, 39 });	//stoped
	shotgun_AFK.PushBack({ 0, 322, 29, 37 });
	

	//WALKING ANIMATIONS

	left.PushBack({ 32, 0, 26, 35 });
	left.PushBack({ 118, 0, 28, 35 });
	left.PushBack({ 0, 0, 29, 32 });
	left.PushBack({ 32, 0, 26, 35 });
	left.PushBack({ 58, 0, 29, 35 });
	left.PushBack({ 87, 0, 28, 35 });
	left.loop = true;
	left.speed = 0.22f;

	up_left.PushBack({ 0, 37, 28, 35 });
	up_left.PushBack({ 32, 37, 28, 35 });
	up_left.PushBack({ 63, 38, 28, 35 });
	up_left.PushBack({ 32, 37, 28, 35 });
	up_left.PushBack({ 0, 37, 28, 35 });
	up_left.PushBack({ 95, 36, 27, 35 });
	up_left.PushBack({ 127, 37, 25, 35 });
	up_left.PushBack({ 95, 36, 27, 35 });
	up_left.loop = true;
	up_left.speed = 0.22f;

	down_left.PushBack({ 126, 75, 32, 38 });
	down_left.PushBack({ 95, 78, 28, 36 });
	down_left.PushBack({ 0, 76, 30, 37 });
	down_left.PushBack({ 33, 78, 30, 35 });
	down_left.PushBack({ 95, 78, 28, 36 });
	down_left.PushBack({ 64, 77, 31, 37 });
	down_left.loop = true;
	down_left.speed = 0.22f;

	down.PushBack({ 101, 117, 28, 40 });
	down.PushBack({ 70, 118, 27, 37 });
	down.PushBack({ 131, 116, 28, 39 });
	down.PushBack({ 35, 118, 28, 38 });
	down.PushBack({ 70, 118, 27, 37 });
	down.PushBack({ 0, 118, 28, 38 });
	down.loop = true;
	down.speed = 0.22f;
	//1,5,2,3,4
	up.PushBack({ 2, 156, 29, 39 });
	up.PushBack({ 120, 156, 29, 39 });
	up.PushBack({ 32, 156, 29, 39 });
	up.PushBack({ 62, 156, 29, 39 });
	up.PushBack({ 92, 156, 29, 38 });
	up.loop = true;
	up.speed = 0.22f;

	up_right.PushBack({ 67, 199, 23, 35 });
	up_right.PushBack({ 35, 197, 25, 37 });
	up_right.PushBack({ 6, 198, 24, 36 });
	up_right.PushBack({ 93, 198, 27, 36 });
	up_right.PushBack({ 35, 197, 25, 37 });
	up_right.PushBack({ 129, 197, 22, 37 });
	up_right.loop = true;
	up_right.speed = 0.22f;

	right.PushBack({ 36, 236, 29, 38 });
	right.PushBack({ 6, 237, 27, 38 });
	right.PushBack({ 129, 238, 27, 37 });
	right.PushBack({ 68, 238, 29, 35 });
	right.PushBack({ 6, 237, 27, 38 });
	right.PushBack({ 98, 237, 29, 36 });
	right.loop = true;
	right.speed = 0.22f;

	down_right.PushBack({ 7, 279, 28, 36 });
	down_right.PushBack({ 35, 278, 28, 37 });
	down_right.PushBack({ 67, 277, 27, 37 });
	down_right.PushBack({ 104, 276, 25, 37 });
	down_right.PushBack({ 131, 277, 28, 37 });
	down_right.loop = true;
	down_right.speed = 0.22f;

	//shotgun movement
	shotgun_walk.PushBack({0,322,29,37});
	shotgun_walk.PushBack({33,322,30,36});
	shotgun_walk.PushBack({65,322,30,36});
	shotgun_walk.PushBack({98,322,30,38});
	shotgun_walk.loop = true;
	shotgun_walk.speed = 0.22f;
}

ModulePlayer::~ModulePlayer()
{}


bool ModulePlayer::Start()
{
	LOG("Loading player ");
	//Reset position
	position.x = 100;
	position.y = 220;
	//Add collider
	body = App->collision->AddCollider({ position.x, position.y, 30, 40 }, COLLIDER_PLAYER, this);
	//Load character sprites
	graphics = App->textures->Load("character_sprites.png");
	

	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	//Delete the collider
	App->collision->EraseCollider(body);
	//Delete character sprites
	App->textures->Unload(graphics);

	return true;
}


update_status ModulePlayer::Update()
{
	float speed = 2.0f;
	//AFK
	if (shotgun)current_animation = &shotgun_AFK;
	else current_animation = &idle; 
	
	
	//Movement

	//right down
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT&&App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{

			if (position.y <= last_position + 65)
			{
				if (position.x <= 210){ position.x += speed / 1.5f; }
				position.y += speed;
			}
			else if (position.x <= 210) { position.x += speed / 1.5f; }

			if (shotgun == false){
				if (current_animation != &down_right)
				{
					idle.Reset();
					current_animation = &down_right;
				}
				//laser shot
				if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
					App->particles->AddParticle(App->particles->laser_south_east_fire, position.x+14, position.y+18, COLLIDER_NONE);
					App->particles->AddParticle(App->particles->laser_south_east_bullet, position.x+14, position.y+18, COLLIDER_PLAYER_SHOT);
				}
			}
			else if(current_animation != &shotgun_walk)
			{
				idle.Set_frame(1);
				current_animation = &shotgun_walk;
			}
	}

	//right up
	else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT&&App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT){

		if (position.y <= last_position)
		{
			if (position.x <= 210)
			{
				position.x += speed / 1.5f;
			}
			position.y -= speed;
			App->render->camera.y += speed * 2;
			last_position = position.y;
		}
		else {
			if (position.x <= 210)
			{
				position.x += speed / 1.5f;
			}
			position.y -= speed;
		}
		if (shotgun == false){
			if (current_animation != &up_right)
			{
				idle.Reset();
				current_animation = &up_right;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_north_east_fire, position.x + 22, position.y - 16, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_north_east_bullet, position.x + 26, position.y - 16, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
	}

	//left down
	else if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		
		if (position.y <= last_position + 65)
		{
			if (position.x > 0){ position.x -= speed / 1.5f; }
			position.y += speed;
		}
		else if (position.x >= 0) { position.x -= speed / 1.5f; }

		if (shotgun == false){
			if (current_animation != &down_left)
			{
				idle.Reset();
				current_animation = &down_left;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_south_west_fire, position.x-15, position.y + 13, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_south_west_bullet, position.x-13, position.y + 13, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
	}

	//left up
	else if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT&&App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{

		if (position.y <= last_position)
		{
			if (position.x >= 0)
			{
				position.x -= speed / 1.5f;
			}
			position.y -= speed;
			App->render->camera.y += speed * 2;
			last_position = position.y;
		}
		else {
			if (position.x >= 0)
			{
				position.x -= speed / 1.5f;
			}
			position.y -= speed;
		}


		if (shotgun == false)
		{
			if (current_animation != &up_left)
			{
				idle.Reset();
				current_animation = &up_left;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_north_east_fire, position.x + 22, position.y - 16, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_north_east_bullet, position.x + 26, position.y - 16, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
	}

	//right
	else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT){
		if (position.x < 210){
			position.x += speed;
		}

		if (shotgun == false){
			if (current_animation != &right)
			{
				idle.Reset();
				current_animation = &right;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_east_fire, position.x + 28, position.y+5, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_east_bullet, position.x + 28, position.y + 8, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
	}

	//left
	else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT){
		if (position.x > 0){
			position.x -= speed;
		}

		if (shotgun == false){
			if (current_animation != &left)
			{
				idle.Reset();
				current_animation = &left;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_west_fire, position.x-18, position.y, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_west_bullet, position.x - 18, position.y+5, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
	}

	//up
	else if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{


		if (position.y <= last_position){
			position.y -= speed;
			App->render->camera.y += speed * 2;
			last_position = position.y;
		}
		else position.y -= speed;

		if (shotgun == false){
			if (current_animation != &up)
			{
				idle.Reset();
				current_animation = &up;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_north_fire, position.x + 13, position.y - 18, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_north_bullet, position.x + 18, position.y - 18, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
		


	}
	
	//down
	else if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y <= last_position + 65)
		{
			position.y += speed;

		}


		if (shotgun == false){
			if (current_animation != &down)
			{
				idle.Reset();
				current_animation = &down;
			}
			//laser shot
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
				App->particles->AddParticle(App->particles->laser_south_fire, position.x, position.y + 24, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->laser_south_bullet, position.x+5, position.y + 24, COLLIDER_PLAYER_SHOT);
			}
		}
		else if (current_animation != &shotgun_walk)
		{
			idle.Set_frame(1);
			current_animation = &shotgun_walk;
		}
	}

	//Weapons
	//AFK laser shot
	if (current_animation == &idle&&App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN)App->particles->AddParticle(App->particles->laser_north_fire, position.x + 13, position.y - 18, COLLIDER_NONE);
	//change weapon
	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
	{
		if(shotgun)shotgun = false;
		else shotgun = true;
	}
	
	//shotgun lvl 1 shoot
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN&&shotgun){

		App->particles->AddParticle(App->particles->shotgun_fire, position.x - 5, position.y - 18, COLLIDER_NONE);
		App->particles->AddParticle(App->particles->shotgun_left, position.x - 5, position.y - 18, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shotgun_mid, position.x + 10, position.y - 18, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shotgun_right, position.x + 23, position.y - 18, COLLIDER_PLAYER_SHOT);
	}

	//Update Player Collider Position-----------------------
	if (IsEnabled()){
		body->SetPos(position.x, position.y);
	}

	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == body && destroyed == false && App->change_scene->IsFading() == false)
	{
		App->change_scene->ChangeScene((Module*)App->lvl_1, (Module*)App->welcome);
		destroyed = true;
	}
}

