#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"

class Bird 
{
public:
  
  Bird( cocos2d::Layer *layer );
    
  void fall();
  
  void fly() { CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( WING_AUDIO  );  isFalling = false; };
  
  void stopFlying( float dt ) { isFalling = true; }

  private:
  
  cocos2d::Size visibleSize;
  cocos2d::Vec2 origin;
  
  cocos2d::Sprite *fBird;
  
  bool isFalling;
};


  