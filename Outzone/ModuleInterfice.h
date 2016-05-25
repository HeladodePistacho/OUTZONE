#ifndef __INTERFICE__
#define __INTERFICE__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#define MAX_ELEMENTS 50

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
	Element energy_bar;
	Element energy_segment;
	Element lives_decoration;
	Element p1_title;
	Element p2_title;
	Element top_title;
	Element bombs;
};

#endif