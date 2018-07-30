#pragma once

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
  
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
private:
  void GoToGameScene(Ref* sender);
};

