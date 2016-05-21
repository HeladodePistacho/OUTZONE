#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_AUDIOS 50
#define MAX_FX 200

class ModuleAudio : public Module
{
public:
	Mix_Music* audios[MAX_AUDIOS];
	Mix_Chunk* efects[MAX_FX];
	uint last_audio = 0;
	uint last_efect = 0;
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const Load(const char* path);
	Mix_Chunk* const Load_chunk(const char* path);
	
};

#endif