#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "MainMenuScene.h"
#include "Definition.h"
using namespace cocos2d;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}




bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init firstc
    if ( !Scene::init() )
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( HIT_AUDIO  );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( POINT_AUDIO  );
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( WING_AUDIO  );

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
  
    auto background = Sprite::create(SPLASHSCENE_BACKGROUND);
    background->setPosition(Vec2((visibleSize.width / 2 + origin.x), (visibleSize.height /2 +  origin.y)));
    this->addChild(background);
      
    this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), SPLASHSCENE_DISPLAY_TIME);
    
    
    return true;
}


 
void SplashScene::GoToMainMenuScene(float dt)
{
 auto scene = MainMenuScene::createScene();
 Director::getInstance()->replaceScene(TransitionFade::create( TRANSITION_TIME,scene));
}
