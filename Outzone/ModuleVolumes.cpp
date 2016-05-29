#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleVolumes.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"

ModuleVolumes::ModuleVolumes()
{
	for (uint i = 0; i < MAX_ACTIVE_VOLUMES; ++i)
		active[i] = nullptr;

	//COLUMNS
	//column 1
	column_1.volume_sprite.PushBack({ 0, 97, 32, 32 });
	column_1.volume_sprite.loop = true;
	column_1.type = STATIC;
	//column 2
	column_2.volume_sprite.PushBack({ 35, 98, 34, 31 });
	column_2.volume_sprite.loop = true;
	column_2.type = STATIC;
	//column 3
	column_3.volume_sprite.PushBack({ 72, 98, 32, 31 });
	column_3.volume_sprite.loop = true;
	column_3.type = STATIC;
	//BLUE SHIP
	//ship left
	blue_ship_left.volume_sprite.PushBack({ 0, 0, 129, 96 });
	blue_ship_left.volume_sprite.loop = true;
	blue_ship_left.type = STATIC;
	//ship right
	blue_ship_right.volume_sprite.PushBack({ 133, 13, 77, 83 });
	blue_ship_right.volume_sprite.loop = true;
	blue_ship_right.type = STATIC;
	//DOOR WALLS
	//left wall
	door_wall_left.volume_sprite.PushBack({ 0, 140, 93, 65 });
	door_wall_left.volume_sprite.loop = true;
	door_wall_left.type = STATIC;
	//right wall
	door_wall_right.volume_sprite.PushBack({ 103, 140, 77, 71 });
	door_wall_right.volume_sprite.loop = true;
	door_wall_right.type = STATIC;
	//CAR COVER
	car_cover.volume_sprite.PushBack({ 0, 205, 66, 67 });
	car_cover.volume_sprite.loop = false;
	car_cover.type = STATIC;
	//BOMB
	bomb.volume_sprite.PushBack({ 375, -20, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 620, -20, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 860, 0, 220, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 1080, 0, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 1330, 0, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 375, 325, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 620, 325, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 860, 317, 230, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 1089, 317, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 1325, 317, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 375, 634, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 620, 634, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 842, 634, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.PushBack({ 1079, 634, 240, 317 });
	bomb.volume_sprite.PushBack({ 1320, 640, 240, 318 });//flash
	bomb.volume_sprite.speed = 0.4f;
	bomb.volume_sprite.loop = false;
	bomb.type = DINAMIC;
}

ModuleVolumes::~ModuleVolumes()
{}

bool ModuleVolumes::Start()
{
	LOG("Loading volumes");
	graphics = App->textures->Load("Volumes_sprites.png");

	return true;
}

bool ModuleVolumes::CleanUp()
{
	LOG("Unloading volumes");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_VOLUMES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleVolumes::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_VOLUMES; ++i)
	{
		Volume* p = active[i];

		if (p == nullptr)
			continue;
		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else{
			if (active[i]->type == DINAMIC){
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->volume_sprite.GetCurrentFrame()), false);
			}
			else{
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->volume_sprite.GetCurrentFrame()));
			}
		}
		
	}

	return UPDATE_CONTINUE;
}

void ModuleVolumes::AddVolume(const Volume& volume, int x, int y)
{
	for (uint i = 0; i < MAX_ACTIVE_VOLUMES; ++i)
	{
		if (active[i] == nullptr)
		{
			Volume* p = new Volume(volume);
			p->position.x = x;
			p->position.y = y;
			active[i] = p;
			break;
		}
	}
}


Volume::Volume()
{
	//position.SetToZero();
}

Volume::Volume(const Volume& p):
volume_sprite(p.volume_sprite), position(p.position)
{}

Volume::~Volume()
{
}

bool Volume::Update()
{
	bool ret = true;
	if ((position.y * -2) < (App->render->camera.y - (App->render->camera.h * 2)-1)){
		ret = false;
		//realment no es borrar 
	}
	if (volume_sprite.Finished() && volume_sprite.loop == false)ret = false;
	return ret;
}

bool Volume::Move(int x,int y){
	position.x = x;
	position.y = y;
	return true;
}