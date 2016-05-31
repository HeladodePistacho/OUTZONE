#ifndef __INTERFICE__
#define __INTERFICE__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#define MAX_ELEMENTS 250

struct SDL_Texture;

struct Element{
	Animation element_animation;
	iPoint position;
	Element();
	Element(int x, int y, Animation anim);
	virtual ~Element();
};

class ModuleInterfice : public Module
{
public:

	ModuleInterfice();
	~ModuleInterfice();

	bool Start();
	update_status Update();
	bool CleanUp();
	
	bool AddElement(int x, int y, Element added);


private:

	Element* elements[MAX_ELEMENTS];
	SDL_Texture* sprites;

public:
	//PLAYER INTERFICE
	Element energy_bar;
	Element energy_segment;
	Element lives_decoration;
	Element p1_title;
	Element p2_title;
	Element top_title;
	Element bomb_icon;
	Element empty_energy_alert;
	Element go_ahead_alert;

	//Last alert added
	Uint32 last_alert;
	//Alert rate
	Uint32 alert_rate;
	//Last empty energy alert
	Uint32 last_energy_alert;
	//Empty alert rate
	Uint32 energy_alert_rate;

	//Current score
	char score_text[10];
	uint score = 0;
	int score_font = -1;
	//Top score
	char top_score_text[10];
	uint top_score = 500;
	//Lives
	char lives_text[4];
	uint lives = 2;
	int lives_font = -1;
	//Bombs
	uint bombs = 3;
	uint bombs_limit = 10;
	//Energy
	int energy = 900;
	uint energy_limit = 36;

	//Counters
	uint bombs_printed;
	uint e_segments_printed;

	//DEBUG COUNT MODE
	//laser shots
	char laser_text[14];
	char* laser_shots = "LASER:";
	char laser_count_text[6];
	int laser_shots_count = 0;
	//shotgun shots
	char shotgun_text[16];
	char* shotgun_shots = "SHOTGUN:";
	char shotgun_count_text[6];
	int shotgun_shots_count = 0;
	//enemies defeated
	char enemies_text[10];
	char* enemies_defeated = "KILLS:";
	char enemies_count_text[6];
	int enemies_def_count = 0;
	//enemies shots
	char enemies_shots_text[12];
	char* enemies_shots= "E.BULLETS:";
	char enemies_shots_count_text[6];
	int enemies_shots_count = 0;
	//enemies spawns
	char enemies_spawns_text[12];
	char* enemies_spawns = "E.ALIVE:";
	char enemies_spawns_count_text[6];
	int enemies_init_spawns_count = 0;

	//timing
	char time_count_text[14];
	char time_text[6];
	char*time = "TIME";
	int initial_time = 0;
	int crone_time = 0;
	int ratio = 1000;
	int seconds = 0;
	int decimes = 0;
	int minutes = 0;

	//debug used font
	int debug_font = -1;
};

#endif