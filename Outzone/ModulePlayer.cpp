#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Module_lvl_1.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include"ModuleRender.h"
ModulePlayer::ModulePlayer()
{

	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 220;

	idle.PushBack({ 32, 0, 26, 35 });

	//WALKING ANIMATIONS

	left.PushBack({ 32, 0, 26, 35 });
	left.PushBack({ 118, 0, 28, 35 });
	left.PushBack({ 0, 0, 29, 32});
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

	Down.PushBack({ 101, 117, 28, 40 });
	Down.PushBack({ 70, 118, 27, 37 });
	Down.PushBack({ 131, 116, 28, 39 });
	Down.PushBack({ 35, 118, 28, 38 });
	Down.PushBack({ 70, 118, 27, 37 });
	Down.PushBack({ 0, 118, 28, 38 });
	Down.loop = true;
	Down.speed = 0.22f;
	
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprite_sheet_main.png"); 
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}


// Update: draw background
update_status ModulePlayer::Update()
{
	current_animation = &idle;
	float speed = 1.0f;

	if (position.x > 0 && position.x < 240  && position.y < 280)
	
	

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN)
	{
		if (position.x > 0 && position.x < 240){ position.x -= speed;}
		
		if (current_animation != &left)
		{
			idle.Reset();
			current_animation = &left;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN)
	{
		if (position.x > 0 && position.x < 240){ position.x -= speed / 4; }
		if (position.y == 220) { App->lvl_1->background.y -= speed; }
		else(position.y -= speed);

		if (current_animation != &up_left)
		{
			idle.Reset();
			current_animation = &up_left;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
	{
		
		if (position.x > 0 && position.y < 280)
		{ 
			position.y += speed; 
			position.x -= speed / 4;
		}
		
		if (current_animation != &down_left)
		{
			idle.Reset();
			current_animation = &down_left;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
	{
		if (position.y < 280){ position.y += speed; }

		if (current_animation != &Down)
		{
			idle.Reset();
			current_animation = &Down;
		}
	}



	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN)
	{
		
		App->lvl_1->background.y -= speed;
	}
	

	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}

