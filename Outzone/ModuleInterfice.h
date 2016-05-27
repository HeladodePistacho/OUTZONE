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
	uint energy;
	uint energy_limit = 36;

	//Counters
	uint bombs_printed;
	uint e_segments_printed;
};

#endif