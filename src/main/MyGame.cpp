#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "MyGame.h"
#define PI 3.14159265

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	sun = new DisplayObjectContainer("sun","./resources/character/sun1.png");
	sun->x = 550;
	sun->y = 400;
	sun->pivotX = sun->width/2;
	sun->pivotY = sun->height/2;
	DisplayObjectContainer * earth = new DisplayObjectContainer("earth","./resources/character/earth.png");
	earth->addChild(new DisplayObject("moon","./resources/character/moon.png"));
	earth->children[0]->x = 90;
	earth->children[0]->y = 90;
	earth->children[0]->pivotX = 50;
	earth->children[0]->pivotY = 50;
	earth->children[0]->scaleX = .6;
	earth->children[0]->scaleY = .6;
	sun->addChild(earth);
	sun->children[0]->x = 250;
	sun->children[0]->y = 250;
	sun->children[0]->pivotX = 50;
	sun->children[0]->pivotY = 50;
	sun->children[0]->scaleX = .75;
	sun->children[0]->scaleY = .75;
	DisplayObjectContainer * venus = new DisplayObjectContainer("venus","./resources/character/venus.png");
	venus->addChild(new DisplayObject("blade", "./resources/character/beyblade.png"));
	venus->children[0]->x = 69;
	venus->children[0]->y = 69;
	venus->children[0]->pivotX = 50;
	venus->children[0]->pivotY = 50;
	venus->children[0]->scaleX = .4;
	venus->children[0]->scaleY = .4;
	sun->addChild(venus);
	sun->children[1]->x = 100;
	sun->children[1]->y = -100;
	sun->children[1]->pivotX = 50;
	sun->children[1]->pivotY = 50;
	sun->children[1]->scaleX = .5;
	sun->children[1]->scaleY = .5;
	//ani = new AnimatedSprite();
}

MyGame::~MyGame(){
	delete sun;
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);
	sun->rotate(1);
	sun->children[0]->rotate(1);
	sun->children[1]->rotate(5);
	bool p = false;
	for (auto k : pressedKeys){
		switch (k) {
			case SDL_SCANCODE_UP:
				sun->move(0,-1 - sun->scaleY);
				break;
			case SDL_SCANCODE_DOWN:
				sun->move(0,1 + sun->scaleY);
				break;
			case SDL_SCANCODE_LEFT:
				sun->move(-1 - sun->scaleX,0);
				break;
			case SDL_SCANCODE_RIGHT:
				sun->move(1 + sun->scaleX,0);
				break;
			case SDL_SCANCODE_Q:
				sun->scale(0.95, 0.95);
				break;
			case SDL_SCANCODE_W:
				sun->scale(1.05, 1.05);
				break;
			case SDL_SCANCODE_A:
				sun->rotate(-2);
				break;
			case SDL_SCANCODE_S:
				sun->rotate(2);
				break;
			case SDL_SCANCODE_P:
				sun->loadTexture("./resources/character/Sinistar.png");
				p = true;
				break;
		}
	}
	if (!p){
		sun->loadTexture("./resources/character/sun1.png");
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	sun->draw(at);
	SDL_RenderPresent(Game::renderer);
}
