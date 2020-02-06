#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red,green,blue;
	string type = "DisplayObject";
	SDL_Point position = {0, 0};
	//SDL_Point pivot = {0, 0};
	double x = 0;
	double y = 0;
	double pivotX = 0;
	double pivotY = 0;
	double scaleX = 1;
	double scaleY = 1;
	double shearX = 0;
	double shearY = 0;
	double rotation = 0;
	int alpha = 255;
	int speed = 10;
	int width = 100;
	int height = 100;

	bool vis = true;
	bool p_pressed = false;
	bool isRGB = false;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	//added functions
	void processInput(SDL_Scancode pressedKey);
	double dist(SDL_Point &p1, SDL_Point &p2);
	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);
	double calcRotation(SDL_Point &left, SDL_Point &right);

	virtual void rotate(int deg);
	virtual void move(int tx, int ty);
	virtual void scale(double sx, double sy);
private:

	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;

};

#endif
