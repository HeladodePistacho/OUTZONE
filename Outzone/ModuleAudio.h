#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_AUDIOS 50

class ModuleAudio : public Module
{
public:
	Mix_Music* audios[MAX_AUDIOS];
	uint last_audio = 0;
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const Load(const char* path);
	
};

#endif