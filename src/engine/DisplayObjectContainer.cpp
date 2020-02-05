#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>


DisplayObjectContainer::DisplayObjectContainer(){

}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath){
  children.push_back(new DisplayObject(id, filepath));
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue){
  children.push_back(new DisplayObject(id, red, green, blue));
}

DisplayObjectContainer::~DisplayObjectContainer(){
  for (auto dio : children){
    delete dio;
  }
}

int DisplayObjectContainer::numChildren(){
  return children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index){
  return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id){
  for (auto dio : children){
    if (dio->id == id)
      return dio;
  }
  return NULL;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys){

}

void DisplayObjectContainer::draw(AffineTransform &at){
  for (auto kid : children){
    kid->draw(at);
  }
}
