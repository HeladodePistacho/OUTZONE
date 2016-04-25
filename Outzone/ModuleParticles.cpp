#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Particles_sprites.png");

	//SHOTGUN
	
	//Shotgun Fire
	shotgun_fire.anim.PushBack({2,68,38,18});
	shotgun_fire.life = 50;
	
	//Shotgun lvl 1
	//left
	shotgun_left.anim.PushBack({20,51,10,15});
	shotgun_left.speed.y -= 5;
	shotgun_left.speed.x -= 2;
	shotgun_left.life = 1200;
	//mid
	shotgun_mid.anim.PushBack({5,51,10,16});
	shotgun_mid.speed.y -= 5;
	shotgun_mid.life = 1200;
	//right
	shotgun_right.anim.PushBack({35,51,9,15});
	shotgun_right.speed.y -= 5;
	shotgun_right.speed.x += 2;
	shotgun_right.life = 1200;

	//LASER
	
	//Laser fires
	//north fire
	laser_north_fire.anim.PushBack({ 112, 26, 16, 18 });
	laser_north_fire.life = 50;
	//north east fire
	laser_north_east_fire.anim.PushBack({133,27,18,17});
	laser_north_east_fire.life = 50;
	//north west fire
	laser_north_west_fire.anim.PushBack({94,29,16,15});
	laser_north_west_fire.life = 50;
	//east fire
	laser_east_fire.anim.PushBack({157,37,18,16});
	laser_east_fire.life = 50;
	//south fire
	laser_south_fire.anim.PushBack({ 112, 45, 16, 18 });
	laser_south_fire.life = 50;
	//south east fire
	laser_south_east_fire.anim.PushBack({133,45,17,16});
	laser_south_east_fire.life = 50;
	//south west fire
	laser_south_west_fire.anim.PushBack({90,47,17,16});
	laser_south_west_fire.life = 50;
	//west fire
	laser_west_fire.anim.PushBack({72,35,18,17});
	laser_west_fire.life = 50;
	
	//Laser bullets
	//north bullet
	laser_north_bullet.anim.PushBack({117,6,6,18});
	laser_north_bullet.speed.y -= 5;
	laser_north_bullet.life = 1200;
	//north east bullet
	laser_north_east_bullet.anim.PushBack({ 151, 10, 14, 15 });
	laser_north_east_bullet.speed.y = -4;
	laser_north_east_bullet.speed.x = 4;
	laser_north_east_bullet.life = 1200;
	//north west bullet
	laser_north_west_bullet.anim.PushBack({ 151, 61, 14, 14 });
	laser_north_west_bullet.speed.y = -4;
	laser_north_west_bullet.speed.x = -4;
	laser_north_west_bullet.life = 1200;
	//east bullet
	laser_east_bullet.anim.PushBack({177,40,18,6});
	laser_east_bullet.speed.x += 5;
	laser_east_bullet.life = 1200;
	//south bullet
	laser_south_bullet.anim.PushBack({ 117, 6, 6, 18 });
	laser_south_bullet.speed.y += 5;
	laser_south_bullet.life = 1200;
	//south east bullet
	laser_south_east_bullet.anim.PushBack({151,61,14,14});
	laser_south_east_bullet.speed.y = 4;
	laser_south_east_bullet.speed.x = 4;
	laser_south_east_bullet.life = 1200;
	//south west bullet
	laser_south_west_bullet.anim.PushBack({ 151, 10, 14, 15 });
	laser_south_west_bullet.speed.y = 4;
	laser_south_west_bullet.speed.x = -4;
	laser_south_west_bullet.life = 1200;
	//west bullet
	laser_west_bullet.anim.PushBack({ 177, 40, 18, 6 });
	laser_west_bullet.speed.x -= 5;
	laser_west_bullet.life = 1200;

	//character explosion
	dead_explosion.anim.PushBack({ 0, 116, 125, 125 });
	dead_explosion.anim.PushBack({ 250, 116, 125, 125 });
	dead_explosion.anim.PushBack({ 125, 116, 125, 125 });
	dead_explosion.anim.PushBack({ 0, 241, 125, 125 });
	dead_explosion.anim.PushBack({ 125, 241, 125, 125 });
	dead_explosion.anim.PushBack({ 0, 366, 125, 125 });
	dead_explosion.anim.PushBack({ 125, 366, 125, 125 });
	dead_explosion.anim.PushBack({ 0, 491, 125, 125 });
	dead_explosion.anim.PushBack({ 125, 491, 125, 125 });
	dead_explosion.anim.loop = false;
	dead_explosion.anim.speed = 0.22f;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}


Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

