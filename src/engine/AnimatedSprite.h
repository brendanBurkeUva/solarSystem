#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

using namespace std;

typedef struct{
	string path;
	string name;
	int frames;
	int framerate;
	bool loop;
}Animation;

class AnimatedSprite : public Sprite{

public:

	AnimatedSprite();
	AnimatedSprite(string id);
	~AnimatedSprite();


	void addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(string animName);

	void play(string animName);
	void replay();
	void stop();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	bool playing = false;
	vector<Animation*> animations;

	virtual void rotate(int deg);
	virtual void move(int tx, int ty);
	virtual void scale(double sx, double sy);

private:

};

#endif
