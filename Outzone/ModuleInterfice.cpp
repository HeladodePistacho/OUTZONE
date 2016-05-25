#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleInterfice.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"


ModuleInterfice::ModuleInterfice()
{
	for (uint i = 0; i < MAX_ELEMENTS; ++i)
		elements[i] = nullptr;
	//Player 1 Title
	p1_title.element_animation.PushBack({ 92, 0, 54, 7 });
	p1_title.element_animation.PushBack({ 152, 0, 54, 7 });
	p1_title.element_animation.speed = 0.2f;
	//Player 2 Title
	p2_title.element_animation.PushBack({ 152, 13, 75, 15 });
	p2_title.element_animation.PushBack({ 152, 33, 75, 15 });
	p2_title.element_animation.speed = 0.2f;
	//Top tile
	top_title.element_animation.PushBack({ 92, 13, 22, 7 });
	//Energy bar
	energy_bar.element_animation.PushBack({ 0, 52, 92, 8 });
	//Energy Segment
	energy_segment.element_animation.PushBack({ 31, 15, 3, 8 });
	//Lives Decoration
	lives_decoration.element_animation.PushBack({ 5, 4, 8, 18 });
	//Bombs
	bombs.element_animation.PushBack({ 44, 27, 8, 18 });
}


Element::Element(){
	position.SetToZero();
}

Element::Element(int x, int y, Animation anim){
	position.x = x;
	position.y = y;
	element_animation = anim;

}

Element::~Element(){

}



// Destructor
ModuleInterfice::~ModuleInterfice()
{

}

bool ModuleInterfice::Start()
{
	sprites = App->textures->Load("interfice.png");
	//Energy bar
	App->interfice->AddElement(0, 17, energy_bar);
	//Lives decoration
	App->interfice->AddElement(0, 1, lives_decoration);
	//Player 1 title
	App->interfice->AddElement(25, 2, p1_title);
	//Player 2 title
	App->interfice->AddElement(165, 2, p2_title);
	//Top title
	App->interfice->AddElement(105, 2, top_title);
	return true;
}


// Called before render is available
update_status ModuleInterfice::Update()
{
		for (uint i = 0; i < MAX_ELEMENTS; ++i){
			if (elements[i] != nullptr){
				App->render->Blit(sprites,elements[i]->position.x, elements[i]->position.y, &(elements[i]->element_animation.GetCurrentFrame()), false);
			}
		}
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInterfice::CleanUp()
{
	LOG("Freeing all elements");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	{
		if (elements[i] != nullptr)
		{
			delete elements[i];
			elements[i] = nullptr;
		}
	}

	return true;
}

bool ModuleInterfice::AddElement( int x, int y, Element added)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	{
		if (elements[i] == nullptr){
			Element*p = new Element(x, y, added.element_animation);
			elements[i] = p;
			ret = true;
			break;
		}
	}
	return ret;
}