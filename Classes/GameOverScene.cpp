#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene( unsigned int tempScore )
{
  score = tempScore;
  
  auto scene = Scene::create();
  
  auto layer = GameOverScene::create();
  
  scene->addChild(layer);
  
    return scene;
}



// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto backgroundSprite = Sprite::create( MAIN_MENU_BACKGROUND);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( backgroundSprite );

    auto retryItem = MenuItemImage::create(RETRY_BUTTON, RETRY_BUTTON_CLICKED, CC_CALLBACK_1( GameOverScene::GoToGameScene, this ));
    retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3) );
    
    auto menuItem = MenuItemImage::create(MENU_BUTTON, MENU_BUTTON_CLICKED, CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ));
    menuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );
    
    auto menu = Menu::create( retryItem, menuItem, NULL );
    menu->setPosition(Point::ZERO);
    
    this->addChild( menu );
    
    UserDefault *def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey( "HIGHSCORE", 0 );
    
    if( score > highScore )
    {
      highScore = score;
      def->setIntegerForKey( "HIGHSCORE", highScore );
      
    }
    
    __String *tempScore = __String::createWithFormat("%i", score);
    
    auto current_Score = LabelTTF::create( tempScore->getCString(), LABEL_FONT, visibleSize.height * SCORE_FONT_SIZE );
    current_Score->setPosition(Point( visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y ));
    
    this->addChild( current_Score );
    
    __String *tempHighScore = __String::createWithFormat( "%i", highScore );
    
    auto highScoreLabel = LabelTTF::create( tempHighScore->getCString(), LABEL_FONT, visibleSize.height * SCORE_FONT_SIZE );
    highScoreLabel->setColor( Color3B::YELLOW );
    highScoreLabel->setPosition( Point( visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( highScoreLabel );
    return true;
}


void GameOverScene::GoToMainMenuScene(Ref* sender)
{

  auto scene =  MainMenuScene::createScene();
  Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
  
}

void GameOverScene::GoToGameScene( Ref* sender )
{

  
  auto scene =  GameScene::createScene();
  Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
  
}
