#ifndef __MODULEVOLUMES_H__
#define __MODULEVOLUMES_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

#define MAX_ACTIVE_VOLUMES 50

struct SDL_Texture;

struct Volume
{
	iPoint position;
	Animation volume_sprite;
	Volume();
	Volume(const Volume& p);
	~Volume();
	bool Update();
};

class ModuleVolumes : public Module
{
public:
	ModuleVolumes();
	~ModuleVolumes();

	bool Start();
	update_status Update();
	bool CleanUp();



	void AddVolume(const Volume& particle, int x, int y);


private:

	SDL_Texture* graphics = nullptr;
	Volume* active[MAX_ACTIVE_VOLUMES];
	uint last_particle = 0;

public:

	//Columns
	Volume column_1;
	Volume column_2;
	Volume column_3;

	//Blue ship
	Volume blue_ship_left;
	Volume blue_ship_right;
	
	//Door walls
	Volume door_wall_left;
	Volume door_wall_right;

	//Car cover
	Volume car_cover;

	//Bomb
	Volume bomb;
};

#endif // __MODULEVOLUMES_H__