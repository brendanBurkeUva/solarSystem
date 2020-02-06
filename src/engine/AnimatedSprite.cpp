#include "AnimatedSprite.h"

using namespace std;


AnimatedSprite::AnimatedSprite() : Sprite(){

}

AnimatedSprite::AnimatedSprite(string id) : Sprite(){

}

AnimatedSprite::~AnimatedSprite(){

}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop){
  Animation a = {basepath, animName, numFrames, frameRate, loop};
  animations.push_back(&a);
}

Animation* AnimatedSprite::getAnimation(string animName){
  for (auto a : animations){
    if (a->name == animName){
      return a;
    }
  }
  return NULL;
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys){

}

void AnimatedSprite::draw(AffineTransform &at){

}
