#pragma once

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene( unsigned int tempScore  );

    virtual bool init();
    
    // a selector callback
   
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
private:
  void GoToMainMenuScene( cocos2d::Ref *sender );
  void GoToGameScene( cocos2d::Ref *sender );
  
};


