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
	//for (auto k : pressedKeys){
	//	switch (k) {
	//		case SDL_SCANCODE_UP:
	//			y += -1 - scaleY;
	//			break;
	//		case SDL_SCANCODE_DOWN:
	//			y += 1 + scaleY;
	//			break;
	//		case SDL_SCANCODE_LEFT:
	//			x += -1 - scaleX;
	//			break;
	//		case SDL_SCANCODE_RIGHT:
	//			x += 1 + scaleX;
	//			break;
	//		case SDL_SCANCODE_Q:
	//			scaleX *= 0.95;
	//			scaleY *= 0.95;
	//			break;
	//		case SDL_SCANCODE_W:
	//			scaleX *= 1.05;
	//			scaleY *= 1.05;
	//			break;
	//		//Rotates not fully functional, will finish soon
	//		case SDL_SCANCODE_A:
	//			//at.rotate(-0.05);
	//			rotation--;
	//			break;
	//		case SDL_SCANCODE_S:
	//			//at.rotate(0.05);
	//			rotation++;
	//			break;
	//		case SDL_SCANCODE_I:
	//			pivotY--;
	//			break;
	//		case SDL_SCANCODE_J:
	//			pivotX--;
	//			break;
	//		case SDL_SCANCODE_K:
	//			pivotY++;
	//			break;
	//		case SDL_SCANCODE_L:
	//			pivotX++;
	//			break;
	//		case SDL_SCANCODE_P:
	//			if (!p_pressed){
	//				vis = !vis;
	//				p_pressed = true;
	//			}
	//			break;
	//		case SDL_SCANCODE_Z:
	//			if (alpha > 0)
	//				alpha--;
	//			break;
	//		case SDL_SCANCODE_X:
	//			if (alpha < 255)
	//				alpha++;
	//			break;
	//	}
	//}
	//if (pressedKeys.find(SDL_SCANCODE_P) == pressedKeys.end()){
	//	p_pressed = false;
	//}
}

void DisplayObject::draw(AffineTransform &at){
	//if the object has a texture to draw and is not invisible.
	if(curTexture != NULL && this->vis){
		//apply transforms to move into position. Adjust for pivot after that.
		applyTransformations(at);
		at.translate(-pivotX, -pivotY);
		//std::cout << "Pos: " << x << ", " << y << std::endl;
		//std::cout << "Piv: " << pivotX << ", " << pivotY << std::endl;
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
		at.translate(pivotX, pivotY);
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
}

void DisplayObject::reverseTransformations(AffineTransform &at){
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-(rotation*(PI / 180.0)));
	at.translate(-x,-y);
}

double DisplayObject::calcRotation(SDL_Point &left, SDL_Point &right){
	double rads = atan2(right.y - left.y, right.x - left.x);
	double deg = rads*180/3.1415;
	return deg;
}
