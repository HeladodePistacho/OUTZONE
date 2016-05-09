//CHESTS NOT WORKING
#ifndef _OBJECT_
#define _OBJECT_

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum  STATE{
	CLOSE,
	OPEN
};

class Object{
protected:
	Animation* object_animation;
	Collider* collider;
public:
	iPoint position;
	unsigned int type;
public:
	Object(int x, int y);
	virtual ~Object();
	const Collider* GetCollider() const;
	virtual void Draw(SDL_Texture* sprites);
	virtual void Update(){};
};
#endif