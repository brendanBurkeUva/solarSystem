#include "AnimatedSprite.h"
#include <string>
#include <iostream>

using namespace std;


AnimatedSprite::AnimatedSprite() : Sprite(){

}

AnimatedSprite::AnimatedSprite(string id) : Sprite(){
  this->id = id;
}

AnimatedSprite::~AnimatedSprite(){

}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop){
  Animation a = {basepath, animName, numFrames, frameRate, loop};
  animations.push_back(a);
}

Animation* AnimatedSprite::getAnimation(string animName){
  for (int i = 0; i < animations.size(); i++){
    if (animations[i].name == animName){
      return &animations[i];
    }
  }
  return NULL;
}

void AnimatedSprite::play(string animName){
  Animation * a = getAnimation(animName);
  fram = 0;
  playing = true;
  cur = a;
}

void AnimatedSprite::replay(){
  fram = 0;
  playing = true;
}

void AnimatedSprite::stop(){
  playing = false;
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys){
  //cout << "Playing: " << cur->name << endl;
  if (playing && cur != NULL){
    string fil = cur->path;
    if (fram < cur->frames*cur->framerate) fram++;
    else if (fram == cur->frames*cur->framerate && cur->loop){
      fram = 1;
    }
    fil += to_string(1+(fram/cur->framerate)%cur->frames) + ".png";
    //cout << fil << endl;
    switchTexture(fil);
  }
}

void AnimatedSprite::draw(AffineTransform &at){
  Sprite::draw(at);
}

void AnimatedSprite::rotate(int deg){
  rotation += deg;
  for (auto kid : children){
    kid->rotate(deg);
  }
}

void AnimatedSprite::move(int tx, int ty){
  x += tx;
  y += ty;
}

void AnimatedSprite::scale(double sx, double sy){
  scaleX *= sx;
  scaleY *= sy;
}
