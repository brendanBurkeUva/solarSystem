#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>
#define PI 3.14159265

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
	//position = {0, 0};
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);

}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys){
}

void DisplayObject::draw(AffineTransform &at){
	//if the object has a texture to draw and is not invisible.
	if(curTexture != NULL && this->vis){
		//apply transforms to move into position. Adjust for pivot after that.
		applyTransformations(at);
		//transform three points of interest. Corners except for bottom left (don't need it)
		SDL_Point origin = at.transformPoint(0,0);
		SDL_Point uRight = at.transformPoint(width, 0);
		SDL_Point lRight = at.transformPoint(width, height);

		//setup the draw rect with correct global x,y location and size based in distance formula.
		SDL_Rect dstrect = { origin.x, origin.y, (int)dist(origin,uRight) , (int)dist(uRight,lRight)  };
		SDL_Point pivot;
		pivot.x=0; pivot.y=0;

		//set the alpha value
		SDL_SetTextureAlphaMod(curTexture, alpha);

		//actually draw the image. calcRotation uses atan2 and returns degrees
		//calc rotation not included in this post.
		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calcRotation(origin, uRight), &pivot, SDL_FLIP_NONE);

		//undo pivot and all the other transformations
		reverseTransformations(at);
	}
}

void DisplayObject::processInput(SDL_Scancode pressedKey){

}

double DisplayObject::dist(SDL_Point &p1, SDL_Point &p2){
	return sqrt(pow((p2.x-p1.x),2.0)+pow((p2.y-p1.y),2.0));
}

void DisplayObject::applyTransformations(AffineTransform &at){
	//at.printMatrix();
	at.translate(x,y);
	at.rotate(rotation*(PI / 180.0));
	at.scale(scaleX, scaleY);
	at.translate(-pivotX, -pivotY);
}

void DisplayObject::reverseTransformations(AffineTransform &at){
	at.translate(pivotX, pivotY);
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-(rotation*(PI / 180.0)));
	at.translate(-x,-y);
}

double DisplayObject::calcRotation(SDL_Point &left, SDL_Point &right){
	double rads = atan2(right.y - left.y, right.x - left.x);
	double deg = rads*180/3.1415;
	return deg;
}

void DisplayObject::rotate(int deg){
	rotation += deg;
}

void DisplayObject::move(int tx, int ty){
	x += tx;
	y += ty;
}

void DisplayObject::scale(double sx, double sy){
	scaleX *= sx;
	scaleY *= sy;
}
