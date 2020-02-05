#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	sun = new DisplayObjectContainer("sun","./resources/character/sun1.png");
	sun->children[0]->x = 550;
	sun->children[0]->y = 400;
	sun->children[0]->pivotX = sun->children[0]->width/2;
	sun->children[0]->pivotY = sun->children[0]->height/2;
	sun->children.push_back(new DisplayObjectContainer("earth","./resources/character/earth.png"));
	sun->children[1]->x = 400;
	sun->children[1]->y = 400;
	sun->children[1]->pivotX = sun->children[0]->x + 50;
	sun->children[1]->pivotY = sun->children[0]->y + 50;
}

MyGame::~MyGame(){
	delete sun;
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);
	for (auto kid : sun->children){
		kid->rotation++;
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	for (auto kid : sun->children){
		kid->draw(at);
	}
	SDL_RenderPresent(Game::renderer);
}
