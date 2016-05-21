#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum PARTICLE_TYPE{
	LASER_SHOT,
	LASER_FIRE,
	LASER_IMPACT,
	SHOTGUN_SHOT,
	SHOTGUN_FIRE,
	SHOTGUN_IMPACT,
	ENEMY_SHOT,
	ENEMY_BIG_SHOT,
	ENEMY_MISSILE,
	UNDEFINED,
};

struct Particle
{
	//particle type
	uint type;
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



	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, PARTICLE_TYPE particle_type, Uint32 delay = 0);
	void OnCollision(Collider*, Collider*);


private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	//Shotgun
	Particle shotgun_fire;
	//Shotgun lvl 1
	Particle shotgun_left_1;
	Particle shotgun_mid_1;
	Particle shotgun_right_1;
	//Shotgun lvl 2
	Particle shotgun_left_2;
	Particle shotgun_mid_2;
	Particle shotgun_right_2;
	//Shotgun lvl 3
	Particle shotgun_left_3;
	Particle shotgun_mid_3;
	Particle shotgun_right_3;
	//Shotgun impact
	Particle shotgun_impact;

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

	//laser impact
	Particle laser_impact;
	

	//Explosions
	Particle dead_explosion;
	Particle basic_enemy_explosion;
	Particle big_enemy_explosion;
	Particle big_turret_fire;
	Particle partial_damage;

	//Enemy bullets
	Particle enemy_shot;
	Particle enemy_big_shot;
	Particle enemy_missile;
	

	//Enemy impacts
	Particle missile_impact;
	Particle big_shot_impact;

};

#endif // __MODULEPARTICLES_H__