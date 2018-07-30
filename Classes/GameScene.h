#pragma once
#include "2d/CCTransition.h"
#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
   
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
  /*
  void SetPhysicsWorld(cocos2d::PhysicsWorld  *world) { sceneWorld = world; };
  
  cocos2d::PhysicsWorld *sceneWorld;*/
  
  void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
   void SpawnPipe(float dt);
    
    cocos2d::PhysicsWorld *sceneWorld;
    
    Pipe pipe;
    
    Bird *bird;
    
    unsigned int score;
    
    void stopFlying( float dt );
    
    void update( float dt );
    
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    
    cocos2d::Label* scoreLable;
};


