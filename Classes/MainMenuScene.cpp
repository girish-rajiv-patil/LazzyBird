#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}



// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
     auto titleSprite = Sprite::create(TITLE);
     titleSprite->setPosition(Vec2(visibleSize.width/2 +origin.x, visibleSize.height - titleSprite->getContentSize().height ));
    
    this->addChild(titleSprite);
    
    auto background = Sprite::create(MAIN_MENU_BACKGROUND);
    background->setPosition(Vec2(visibleSize.width/2 +origin.x, visibleSize.height/2 + origin.y));
  
    this->addChild(background);
    
    auto playItem = MenuItemImage::create(PLAY_BUTTON ,PLAY_BUTTON_CLICKED, CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
   CCLOG("hello");
    playItem->setPosition(Vec2(visibleSize.width/2 +origin.x, visibleSize.height/2 + origin.y));
    
   
    
    auto menu = Menu::create();
    menu->addChild(playItem);
    menu->setPosition(Point::ZERO);
   this->addChild(menu);

    return true;
}

void MainMenuScene::GoToGameScene(Ref* sender)
{
    auto scene = GameScene::createScene();
      CCLOG("hello");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene));
}

