#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>


DisplayObjectContainer::DisplayObjectContainer() : DisplayObject(){

}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id, filepath){
  //children.push_back(new DisplayObject(id, filepath));
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue){
  //children.push_back(new DisplayObject(id, red, green, blue));
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
  DisplayObject::draw(at);
  applyTransformations(at);
  at.translate(pivotX, pivotY);
  for (auto kid : children){
    kid->draw(at);
  }
  at.translate(-pivotX, -pivotY);
  reverseTransformations(at);
}

void DisplayObjectContainer::addChild(DisplayObject* child){
  children.push_back(child);
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child){

}

void DisplayObjectContainer::removeImmediateChild(string id){

}

void DisplayObjectContainer::removeChild(int index){
  if (index < children.size())
    children.erase(children.begin() + index);
  else
    std::cerr << "Index out of bounds, failed to remove child" << std::endl;
}

void DisplayObjectContainer::removeThis(){

}

void DisplayObjectContainer::rotate(int deg){
  rotation += deg;
  for (auto kid : children){
    kid->rotate(deg);
  }
}

void DisplayObjectContainer::move(int tx, int ty){
  x += tx;
  y += ty;
  //for (auto kid : children){
  //  kid->move(tx, ty);
  //}
}

void DisplayObjectContainer::scale(double sx, double sy){
  scaleX *= sx;
  scaleY *= sy;
}
