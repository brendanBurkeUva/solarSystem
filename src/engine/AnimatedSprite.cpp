#include "AnimatedSprite.h"
#include <string>

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

void AnimatedSprite::play(string animName){
  Animation * a = getAnimation(animName);
  while (playing){
    int i = 0;
    string fil = a->path;
    if (i % a->framerate == 0) i = (i + 1)%a->framerate;
    fil += to_string(i) + ".png";
    loadTexture(fil);
  }
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys){

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
