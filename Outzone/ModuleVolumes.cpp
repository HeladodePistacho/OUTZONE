#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleVolumes.h"
#include "SDL/include/SDL_timer.h"

ModuleVolumes::ModuleVolumes()
{
	for (uint i = 0; i < MAX_ACTIVE_VOLUMES; ++i)
		active[i] = nullptr;

	//COLUMNS
	//column 1
	column_1.volume_sprite.PushBack({ 0, 97, 32, 32 });
	column_1.volume_sprite.loop = true;
	//column 2
	column_2.volume_sprite.PushBack({ 35, 98, 34, 31 });
	column_2.volume_sprite.loop = true;
	//column 3
	column_3.volume_sprite.PushBack({ 72, 98, 32, 31 });
	column_3.volume_sprite.loop = true;

	//BLUE SHIP
	//ship left
	blue_ship_left.volume_sprite.PushBack({ 0, 0, 129, 96 });
	blue_ship_left.volume_sprite.loop = true;
	//ship right
	blue_ship_right.volume_sprite.PushBack({ 133, 13, 77, 83 });
	blue_ship_right.volume_sprite.loop = true;

	//DOOR WALLS
	//left wall
	door_wall_left.volume_sprite.PushBack({ 0, 140, 93, 71 });
	door_wall_left.volume_sprite.loop = true;
	//right wall
	door_wall_right.volume_sprite.PushBack({ 103, 140, 77, 71 });
	door_wall_right.volume_sprite.loop = true;
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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->volume_sprite.GetCurrentFrame()));
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

Volume::Volume(const Volume& p) :
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
	return ret;
}