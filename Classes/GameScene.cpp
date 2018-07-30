#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
  auto scene = Scene::createWithPhysics( );
   // scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
   scene->getPhysicsWorld()->setGravity(Vect( 0, 0 ));
    
    
   auto layer = GameScene::create();
   layer->SetPhysicsWorld(scene->getPhysicsWorld());
   
   scene->addChild(layer);
   return scene;
}



// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLog("hi1");
    
    
    auto backgroundSprite = Sprite::create( MAIN_MENU_BACKGROUND);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    
     CCLog("hi2");
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);
    
    auto edgeNode = Node::create();
     CCLog("hi3");
    edgeNode->setPosition(Vec2(visibleSize.width/2 +origin.x, visibleSize.height/2 + origin.y));
    
    edgeNode->setPhysicsBody( edgeBody );
     CCLog("hi4");
    this->addChild( edgeNode );
    CCLog("hi5");
    
    this->schedule(schedule_selector(GameScene::SpawnPipe ),  SPAWN_PIPE_FREQUENCY * visibleSize.width);
    
    bird = new Bird( this );
    
    auto contactListener = EventListenerPhysicsContact::create();
    
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2( GameScene::onTouchBegan, this );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    score = 0;
    
    __String *tempScore = __String::createWithFormat("%i", score);
    
    scoreLable = Label::createWithTTF(tempScore->getCString(), LABEL_FONT , visibleSize.height * SCORE_FONT_SIZE); 
    scoreLable->setColor( Color3B::WHITE );
    scoreLable->setPosition( Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y) );
    this->addChild( scoreLable, 1000 );
    
    
    
    this->scheduleUpdate(  );
    
    return true;
}




void GameScene::SpawnPipe(float dt)
{
  pipe.SpawnPipe( this );
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
  PhysicsBody *a = contact.getShapeA()->getBody();
  PhysicsBody *b = contact.getShapeB()->getBody();

  
  if((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() &&  OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK ==  a->getCollisionBitmask()))
  {
   
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( HIT_AUDIO  );
    
    auto scene = GameOverScene::createScene( score );
    
    Director::getInstance()->replaceScene(TransitionFade :: create(TRANSITION_TIME , scene));
  }
  else if((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() &&  POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK ==  a->getCollisionBitmask()))
  {
   
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( POINT_AUDIO  );
    score++;
    
    __String *tempScore = __String::createWithFormat("%i", score);
       scoreLable->setString( tempScore->getCString() );
  }
  
  return true;
}


    
bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
  bird->fly();
  this->scheduleOnce(schedule_selector( GameScene::stopFlying) , FLY_DURATION );
  
  return true;
}
 
void GameScene::stopFlying(float dt)
{
 
 bird->stopFlying(FLY_DURATION); 
  
}
 
void GameScene::update(float dt)
{
  bird->fall();
}
 
 

