#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleInterfice.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "Module_lvl_1.h"
#include "Module_Welcome.h"
#include <stdio.h>

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
	energy_segment.element_animation.PushBack({ 94, 52, 1, 8 });
	energy_segment.element_animation.loop = false;
	//Lives Decoration
	lives_decoration.element_animation.PushBack({ 5, 4, 8, 18 });
	//Bombs
	bomb_icon.element_animation.PushBack({ 19, 6, 6, 16 });
	bomb_icon.element_animation.loop = false;
	//Empty energy alert
	empty_energy_alert.element_animation.PushBack({ 4, 96, 42, 26 });
	empty_energy_alert.element_animation.speed = 0.05;
	empty_energy_alert.element_animation.loop = false;
	//Go ahead alert
	go_ahead_alert.element_animation.PushBack({ 34, 0, 52, 48 });
	go_ahead_alert.element_animation.PushBack({ 0, 0, 0, 0 });
	go_ahead_alert.element_animation.speed = 0.02f;
	go_ahead_alert.element_animation.loop = false;

	//Alerts timming
	last_alert = 0;
	alert_rate = 1000;
	last_energy_alert = 0;
	energy_alert_rate = 800;
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
	if (App->lvl_1->IsEnabled()){
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
		energy_alert_rate = 800;
		empty_energy_alert.element_animation.speed = 0.05;
	}
	if (App->welcome->IsEnabled()){
		//Player 1 title
		App->interfice->AddElement(25, 2, p1_title);
	}
	return true;
}


// Called before render is available
update_status ModuleInterfice::Update()
{
	if (IsEnabled()){
		if (App->lvl_1->IsEnabled()){
			//Bombs data
			bombs_printed = 0;
			uint mark = 8;
			uint original_x = 18;

			//Adds the bombs to the elements array
			if (bombs){
				for (int k = 0; k < bombs; k++){
					App->interfice->AddElement(bombs_printed*mark, 304, bomb_icon);
					bombs_printed++;
				}
			}
			//Energy data
			e_segments_printed = 0;
			uint e_mark = 2;
			uint e_original_x = 10;

			//Adds the energy segments to the elements array
			if (energy){
				for (int k = 0; k < energy; k++){
					App->interfice->AddElement(original_x + e_segments_printed*e_mark, 17, energy_segment);
					e_segments_printed++;
				}
			}
			//Print go ahead alert
			if (App->player->current_time>App->player->last_movement + App->player->afk_mark && App->player->current_time > last_alert + alert_rate){
				last_alert = App->player->current_time;
				App->interfice->AddElement(103, 56, App->interfice->go_ahead_alert);
			}
			//Print empty energy alert
			if (energy <= 8 && App->player->current_time > last_energy_alert + energy_alert_rate){
				last_energy_alert = App->player->current_time;
				App->interfice->AddElement(20, 32, App->interfice->empty_energy_alert);
			}
			if (energy == 4 && energy_alert_rate > 400){
				energy_alert_rate /= 2;
				empty_energy_alert.element_animation.speed *= 2;
			}
			else if (energy == 3 && energy_alert_rate > 200){
				energy_alert_rate /= 2;
				empty_energy_alert.element_animation.speed *= 2;
			}
			else if (energy == 1 && energy_alert_rate > 100){
				energy_alert_rate /= 2;
				empty_energy_alert.element_animation.speed *= 2;
			}
			else if (energy == 0){
				empty_energy_alert.element_animation.speed /= 2;
			}
			if (App->player->current_animation == &App->player->energy_dead){
				App->interfice->AddElement(App->player->position.x, App->player->position.y - 15, empty_energy_alert);
			}

			//Draw player UI --------------------------------------------
			//top score
			sprintf_s(top_score_text, 10, "%i", top_score);
			App->fonts->Blit(147, 10, score_font, top_score_text);
			//score
			sprintf_s(score_text, 10, "%i", score);
			App->fonts->Blit(73, 10, score_font, score_text);
			//lives
			sprintf_s(lives_text, 4, "%i", lives);
			App->fonts->Blit(15, 2, lives_font, lives_text);
		}
	}
	if (App->welcome->IsEnabled()){
		//top score
		sprintf_s(top_score_text, 10, "%i", top_score);
		App->fonts->Blit(147, 10, score_font, top_score_text);
		//score
		sprintf_s(score_text, 10, "%i", score);
		App->fonts->Blit(73, 10, score_font, score_text);
	}

	//Deletes the loop false with animation ended elements
	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	{
		if (elements[i] != nullptr && elements[i]->element_animation.loop == false && elements[i]->element_animation.Finished()){
			{
				delete elements[i];
				elements[i] = nullptr;
			}
		}
	}
	//Prints all the alive elements
	for (uint i = 0; i < MAX_ELEMENTS; ++i){
		if (elements[i] != nullptr){
			App->render->Blit(sprites, elements[i]->position.x, elements[i]->position.y, &(elements[i]->element_animation.GetCurrentFrame()), false);
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
	//Unload all the fonts
	App->fonts->UnLoad(score_font);
	App->fonts->UnLoad(lives_font);
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