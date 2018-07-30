#include "Pipe.h"
#include "cocos2d.h"
#include "MainMenuScene.h"
#include "Definition.h"
#include "GameScene.h"
using namespace cocos2d;

Pipe::Pipe()
{
  visibleSize = Director::getInstance()->getVisibleSize();
  origin = Director::getInstance()->getVisibleOrigin();
}



void Pipe::SpawnPipe(cocos2d::Layer* layer)
{
  CCLog("Pipe Created");
  
  auto topPipe = Sprite::create(PIPE);
  auto bottomPipe = Sprite::create(PIPE);
  
  auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize() );
  auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize() );
  
  auto random = CCRANDOM_0_1();
  
  if( random < LOWER_SCENE_PIPE_THRESHOLD )
  {
    random = LOWER_SCENE_PIPE_THRESHOLD;
  }
  else if( random > UPPER_SCENE_PIPE_THRESHOLD )
  {
    random = UPPER_SCENE_PIPE_THRESHOLD;
  }
  
  auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height / 2);
//   auto bottomPipePosition = (random * visibleSize.height) - (bottomPipe->getContentSize().height / 2);
  
  topPipeBody->setDynamic(false);
  bottomPipeBody->setDynamic(false);
  
  topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
  bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
  
  topPipeBody->setContactTestBitmask(true);
  bottomPipeBody->setContactTestBitmask(true);
  
  topPipe->setPhysicsBody(topPipeBody);
  bottomPipe->setPhysicsBody(bottomPipeBody);
  
  topPipe->setPosition(Vec2(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
  
  bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - ( Sprite::create(BALL)->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));
 //bottomPipe->setPosition(Point(visibleSize.width / 2 + bottomPipe->getContentSize().width + origin.x + CCRANDOM_MINUS1_1() * 250, bottomPipePosition));
  auto topPipeAction = MoveBy::create(PIPE_SPEED_MOVEMENT * visibleSize.width,Vec2(-visibleSize.width * 1.5,0));
  auto bottomPipeAction = MoveBy::create(PIPE_SPEED_MOVEMENT * visibleSize.width,Vec2(-visibleSize.width * 1.5,0));
  
  topPipe->runAction(topPipeAction);
  bottomPipe->runAction(bottomPipeAction);
  
  auto pointNode = Node::create();
  auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create(BALL)->getContentSize().height * PIPE_GAP));
  
  pointBody->setDynamic( false );
  pointBody->setCollisionBitmask( POINT_COLLISION_BITMASK );
  pointBody->setContactTestBitmask( true );
  
  pointNode->setPhysicsBody( pointBody );
  pointNode->setPosition( Point( topPipe->getPositionX(), topPipe->getPositionY() - ( topPipe->getContentSize().height /2 ) - (( Sprite::create(BALL)->getContentSize().height * PIPE_GAP) / 2 ) ) );
  
 
  auto pointNodeAction = MoveBy::create(PIPE_SPEED_MOVEMENT * visibleSize.width,Vec2(-visibleSize.width * 1.5,0));
  pointNode->runAction( pointNodeAction );
 
 layer->addChild( pointNode );
 
 layer->addChild( topPipe );
 layer->addChild( bottomPipe );
 
}
