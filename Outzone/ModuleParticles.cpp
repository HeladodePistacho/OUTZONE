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
	//SHOTGUN

	//SHOTGUN FIRE
	shotgun_fire.anim.PushBack({ 0, 65, 36, 16 });
	shotgun_fire.life = 15;
	shotgun_fire.type = SHOTGUN_FIRE;
	
	//SHOTGUN LVL 1
	//left
	shotgun_left_1.anim.PushBack({ 18, 48, 8, 13 });
	shotgun_left_1.speed.y -= 5;
	shotgun_left_1.speed.x -= 2;
	shotgun_left_1.life = 1200;
	shotgun_left_1.type = SHOTGUN_FIRE;
	//mid
	shotgun_mid_1.anim.PushBack({ 4, 48, 6, 14 });
	shotgun_mid_1.speed.y -= 5;
	shotgun_mid_1.life = 1200;
	shotgun_mid_1.type = SHOTGUN_FIRE;
	//right
	shotgun_right_1.anim.PushBack({ 32, 48, 8, 13 });
	shotgun_right_1.speed.y -= 5;
	shotgun_right_1.speed.x += 2;
	shotgun_right_1.life = 1200;
	shotgun_right_1.type = SHOTGUN_FIRE;
	
	//SHOTGUN LVL 2
	//left
	shotgun_left_2.anim.PushBack({ 16, 26, 12, 19 });
	shotgun_left_2.speed.y -= 5;
	shotgun_left_2.speed.x -= 2;
	shotgun_left_2.life = 1200;
	shotgun_left_2.type = SHOTGUN_FIRE;
	//mid
	shotgun_mid_2.anim.PushBack({ 1, 26, 12, 19 });
	shotgun_mid_2.speed.y -= 5;
	shotgun_mid_2.life = 1200;
	shotgun_mid_2.type = SHOTGUN_FIRE;
	//right
	shotgun_right_2.anim.PushBack({ 30, 26, 12, 19 });
	shotgun_right_2.speed.y -= 5;
	shotgun_right_2.speed.x += 2;
	shotgun_right_2.life = 1200;
	shotgun_right_2.type = SHOTGUN_FIRE;
	
	//SHOTGUN LVL 3
	//left
	shotgun_left_3.anim.PushBack({ 15, 0, 15, 24 });
	shotgun_left_3.speed.y -= 5;
	shotgun_left_3.speed.x -= 2;
	shotgun_left_3.life = 1200;
	shotgun_left_3.type = SHOTGUN_FIRE;
	//mid
	shotgun_mid_3.anim.PushBack({ 0, 0, 15, 24 });
	shotgun_mid_3.speed.y -= 5;
	shotgun_mid_3.life = 1200;
	shotgun_mid_3.type = SHOTGUN_FIRE;
	//right
	shotgun_right_3.anim.PushBack({ 31, 0, 14, 23 });
	shotgun_right_3.speed.y -= 5;
	shotgun_right_3.speed.x += 2;
	shotgun_right_3.life = 1200;
	shotgun_right_3.type = SHOTGUN_FIRE;

	//SHOTGUN IMPACT
	shotgun_impact.anim.PushBack({ 215, 54, 25, 25 });
	shotgun_impact.anim.PushBack({ 237, 54, 25, 25 });
	shotgun_impact.anim.PushBack({ 263, 54, 25, 25 });
	shotgun_impact.anim.PushBack({ 288, 54, 25, 25 });
	shotgun_impact.anim.loop = false;
	shotgun_impact.anim.speed = 0.25f;
	shotgun_impact.type = SHOTGUN_IMPACT;





	//LASER

	//Laser fires
	//north fire
	laser_north_fire.anim.PushBack({ 110, 23, 14, 16 });
	laser_north_fire.life = 50;
	laser_north_fire.type = LASER_FIRE;
	//north east fire
	laser_north_east_fire.anim.PushBack({ 131, 25, 16, 14 });
	laser_north_east_fire.life = 50;
	laser_north_east_fire.type = LASER_FIRE;
	//north west fire
	laser_north_west_fire.anim.PushBack({ 92, 26, 14, 13 });
	laser_north_west_fire.life = 50;
	laser_north_west_fire.type = LASER_FIRE;
	//east fire
	laser_east_fire.anim.PushBack({ 155, 32, 16, 15 });
	laser_east_fire.life = 50;
	laser_east_fire.type = LASER_FIRE;
	//south fire
	laser_south_fire.anim.PushBack({ 110, 42, 14, 16 });
	laser_south_fire.life = 50;
	laser_south_fire.type = LASER_FIRE;
	//south east fire
	laser_south_east_fire.anim.PushBack({ 131, 42, 15, 14 });
	laser_south_east_fire.life = 50;
	laser_south_east_fire.type = LASER_FIRE;
	//south west fire
	laser_south_west_fire.anim.PushBack({ 88, 43, 15, 15 });
	laser_south_west_fire.life = 50;
	laser_south_west_fire.type = LASER_FIRE;
	//west fire
	laser_west_fire.anim.PushBack({ 70, 32, 16, 15 });
	laser_west_fire.life = 50;
	laser_west_fire.type = LASER_FIRE;

	//Laser bullets
	//north bullet
	laser_north_bullet.anim.PushBack({ 115, 3, 4, 16 });
	laser_north_bullet.speed.y -= 6;
	laser_north_bullet.life = 1200;
	laser_north_bullet.type = LASER_SHOT;
	//north east bullet
	laser_north_east_bullet.anim.PushBack({ 149, 8, 12, 12 });
	laser_north_east_bullet.speed.y = -4;
	laser_north_east_bullet.speed.x = 4;
	laser_north_east_bullet.life = 1200;
	laser_north_east_bullet.type = LASER_SHOT;

	//north east up bullet
	laser_north_east_up_bullet.anim.PushBack({ 132, 4, 9, 14 });
	laser_north_east_up_bullet.speed.y = -5;
	laser_north_east_up_bullet.speed.x = 3;
	laser_north_east_up_bullet.life = 1200;
	laser_north_east_up_bullet.type = LASER_SHOT;
	//north east down bullet
	laser_north_east_down_bullet.anim.PushBack({ 167, 18, 14, 9 });
	laser_north_east_down_bullet.speed.y = -3;
	laser_north_east_down_bullet.speed.x = 5;
	laser_north_east_down_bullet.life = 1200;
	laser_north_east_down_bullet.type = LASER_SHOT;

	//north west bullet
	laser_north_west_bullet.anim.PushBack({ 149, 58, 12, 12 });
	laser_north_west_bullet.speed.y = -4;
	laser_north_west_bullet.speed.x = -4;
	laser_north_west_bullet.life = 1200;
	laser_north_west_bullet.type = LASER_SHOT;

	//north west up bullet
	laser_north_west_up_bullet.anim.PushBack({ 167, 50, 14, 9 });
	laser_north_west_up_bullet.speed.y = -5;
	laser_north_west_up_bullet.speed.x = -3;
	laser_north_west_up_bullet.life = 1200;
	laser_north_west_up_bullet.type = LASER_SHOT;

	//north west down bullet
	laser_north_west_down_bullet.anim.PushBack({ 130, 62, 9, 14 });
	laser_north_west_down_bullet.speed.y = -3;
	laser_north_west_down_bullet.speed.x = -5;
	laser_north_west_down_bullet.life = 1200;
	laser_north_west_down_bullet.type = LASER_SHOT;

	//east bullet
	laser_east_bullet.anim.PushBack({ 175, 37, 16, 4 });
	laser_east_bullet.speed.x += 6;
	laser_east_bullet.life = 1200;
	laser_east_bullet.type = LASER_SHOT;

	//south bullet
	laser_south_bullet.anim.PushBack({ 115, 3, 4, 16 });
	laser_south_bullet.speed.y += 6;
	laser_south_bullet.life = 1200;
	laser_south_bullet.type = LASER_SHOT;

	//south east bullet
	laser_south_east_bullet.anim.PushBack({ 149, 58, 12, 12 });
	laser_south_east_bullet.speed.y = 4;
	laser_south_east_bullet.speed.x = 4;
	laser_south_east_bullet.life = 1200;
	laser_south_east_bullet.type = LASER_SHOT;

	//south east up bullet
	laser_south_east_up_bullet.anim.PushBack({ 130, 62, 9, 14 });
	laser_south_east_up_bullet.speed.y = 3;
	laser_south_east_up_bullet.speed.x = 5;
	laser_south_east_up_bullet.life = 1200;
	laser_south_east_up_bullet.type = LASER_SHOT;

	//south east down bullet
	laser_south_east_down_bullet.anim.PushBack({ 167, 50, 14, 9 });
	laser_south_east_down_bullet.speed.y = 5;
	laser_south_east_down_bullet.speed.x = 3;
	laser_south_east_down_bullet.life = 1200;
	laser_south_east_down_bullet.type = LASER_SHOT;

	//south west bullet
	laser_south_west_bullet.anim.PushBack({ 149, 8, 12, 12 });
	laser_south_west_bullet.speed.y = 4;
	laser_south_west_bullet.speed.x = -4;
	laser_south_west_bullet.life = 1200;
	laser_south_west_bullet.type = LASER_SHOT;

	//south west up bullet
	laser_south_west_up_bullet.anim.PushBack({ 167, 18, 14, 9 });
	laser_south_west_up_bullet.speed.y = 3;
	laser_south_west_up_bullet.speed.x = -5;
	laser_south_west_up_bullet.life = 1200;
	laser_south_west_up_bullet.type = LASER_SHOT;

	//south west down bullet
	laser_south_west_down_bullet.anim.PushBack({ 132, 4, 9, 14 });
	laser_south_west_down_bullet.speed.y = 5;
	laser_south_west_down_bullet.speed.x = -3;
	laser_south_west_down_bullet.life = 1200;
	laser_south_west_down_bullet.type = LASER_SHOT;

	//west bullet
	laser_west_bullet.anim.PushBack({ 175, 37, 16, 4 });
	laser_west_bullet.speed.x -= 6;
	laser_west_bullet.life = 1200;
	laser_west_bullet.type = LASER_SHOT;

	//laser impact
	laser_impact.anim.PushBack({ 216, 33, 20, 17 });
	laser_impact.anim.PushBack({ 236, 33, 20, 17 });
	laser_impact.anim.PushBack({ 289, 33, 23, 16 });
	laser_impact.anim.PushBack({ 262, 33, 22, 16 });
	laser_impact.anim.PushBack({ 319, 33, 20, 17 });
	laser_impact.anim.loop = false;
	laser_impact.anim.speed = 0.25f;
	laser_impact.type = LASER_IMPACT;

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
	dead_explosion.anim.speed = 0.15f;

	//enemie explosion
	basic_robot_explosion.anim.PushBack({ 9, 647, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 53, 647, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 95, 647, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 140, 647, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 184, 647, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 9, 690, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 53, 690, 44, 43 });
	basic_robot_explosion.anim.PushBack({ 97, 890, 44, 43 });
	basic_robot_explosion.anim.loop = false;
	basic_robot_explosion.anim.speed = 0.2f;

	//enemie shot
	enemie_shot.anim.PushBack({ 0, 112, 6, 6 });
	enemie_shot.life = 2000;
	enemie_shot.type = ENEMY_SHOT;
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Particles_sprites.png");

	return true;
}

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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type,PARTICLE_TYPE particle_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->type = particle_type;
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
fx(p.fx), born(p.born), life(p.life), type(p.type)
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




void ModuleParticles::OnCollision(Collider*c1, Collider*c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		if (c1->type == COLLIDER_PLAYER_SHOT || COLLIDER_ENEMY_SHOT&&c2->type==COLLIDER_WALL||COLLIDER_ENEMY){
			//laser shot impact
			if (active[i] != nullptr && active[i]->collider == c1&&active[i]->type==LASER_SHOT)
			{
				App->particles->AddParticle(App->particles->laser_impact, c1->rect.x-8, c1->rect.y-5, COLLIDER_NONE,LASER_IMPACT);
				delete active[i];
				active[i] = nullptr;
				break;
			}
			//shotgun shot impact
			if (active[i] != nullptr && active[i]->collider == c1 && active[i]->type == SHOTGUN_SHOT)
			{
				App->particles->AddParticle(App->particles->shotgun_impact, c1->rect.x - 8, c1->rect.y-5, COLLIDER_NONE, SHOTGUN_IMPACT);
				delete active[i];
				active[i] = nullptr;
				break;
			}
			//enemy bullet
			//still not working
			if (active[i] != nullptr && active[i]->collider == c1 && active[i]->type == ENEMY_SHOT && c2->type == COLLIDER_PLAYER){
				delete active[i];
				active[i] = nullptr;
				break;
			}
		}
	}
}


