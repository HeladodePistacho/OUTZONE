#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	//Shotgun
	Particle shotgun_fire;
	//Shotgun lvl 1
	Particle shotgun_left;
	Particle shotgun_mid;
	Particle shotgun_right;
	

	//Laser
	//Laser fires
	Particle laser_north_fire;
	Particle laser_north_east_fire;
	Particle laser_north_west_fire;
	Particle laser_east_fire;
	Particle laser_south_fire;
	Particle laser_south_east_fire;
	Particle laser_south_west_fire;
	Particle laser_west_fire;

	//Laser bullets
	//north
	Particle laser_north_bullet;
	Particle laser_north_east_up_bullet;
	Particle laser_north_east_bullet;
	Particle laser_north_east_down_bullet;
	Particle laser_north_west_up_bullet;
	Particle laser_north_west_bullet;
	Particle laser_north_west_down_bullet;
	//east
	Particle laser_east_bullet;
	//south
	Particle laser_south_bullet;
	Particle laser_south_east_up_bullet;
	Particle laser_south_east_bullet;
	Particle laser_south_east_down_bullet;
	Particle laser_south_west_up_bullet;
	Particle laser_south_west_bullet;
	Particle laser_south_west_down_bullet;
	//west
	Particle laser_west_bullet;

	//character explosion
	Particle dead_explosion;

};

#endif // __MODULEPARTICLES_H__