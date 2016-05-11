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
	title.element_animation.PushBack({ 120, 14, 56, 9 });
	title.element_animation.PushBack({ 180, 14, 56, 9 });
	title.element_animation.speed = 0.2f;
	//Top
	top.element_animation.PushBack({ 120, 27, 24, 9 });
	//Energy bar
	energy_bar.element_animation.PushBack({ 13, 63, 94, 10 });
	//Energy Segment
	energy_segment.element_animation.PushBack({ 31, 15, 3, 8 });
	//Lives Decoration
	lives_decoration.element_animation.PushBack({ 29, 27, 8, 18 });
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
	App->interfice->AddElement(App->player->position.x, App->player->position.y, App->interfice->title);
	return true;
}


// Called before render is available
update_status ModuleInterfice::Update()
{
	if (IsEnabled()){
		for (uint i = 0; i < MAX_ELEMENTS; ++i){

			if (elements[i] != nullptr){
				elements[i]->position.y = App->render->camera.y + 50;
				elements[i]->position.y = App->render->camera.x + 50;
				App->render->Blit(sprites, elements[i]->position.x, elements[i]->position.y, &(elements[i]->element_animation.GetCurrentFrame()));
			}
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
		Element*p = new Element(x, y, added.element_animation);
		ret = true;
		break;
	}
	return ret;
}