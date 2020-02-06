#include "Sprite.h"

using namespace std;

Sprite::Sprite() : DisplayObjectContainer(){

}

Sprite::Sprite(string id, string filepath) : DisplayObjectContainer(id, filepath){

}

Sprite::Sprite(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue){

}

void Sprite::update(set<SDL_Scancode> pressedKeys){

}

void Sprite::draw(AffineTransform &at){

}
