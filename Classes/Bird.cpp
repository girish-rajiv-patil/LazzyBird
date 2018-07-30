#include "Bird.h"
#include "cocos2d.h"

#include "Definition.h"
#include "GameScene.h"
using namespace cocos2d;

Bird::Bird( cocos2d::Layer* layer)
{
  visibleSize = Director::getInstance()->getVisibleSize();
  origin = Director::getInstance()->getVisibleOrigin();

  
  
  fBird = Sprite::create(BALL);
  fBird->setScale(3.0);

/*  
    auto pinfo = AutoPolygon::generatePolygon( "BBB.png" );
  
    fBird = Sprite::create(pinfo);
    auto birdBody = PhysicsBody::createPolygon(Vec2(visibleSize.width/2 + origin.x, visibleSize.height /2 + origin.y));*/
  
   fBird->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height /2 + origin.y));
  
  auto birdBody = PhysicsBody::createCircle(fBird->getContentSize().width / 2);
    //auto birdBody = PhysicsBody::createEdgePolygon(fBird->getPosition(), PHYSICSBODY_MATERIAL_DEFAULT);
  
  birdBody->setCollisionBitmask( BIRD_COLLISION_BITMASK);
  birdBody->setContactTestBitmask(true);

  fBird->setPhysicsBody( birdBody );
  
  layer->addChild( fBird, 100 );
  
  isFalling = true;
}

void Bird::fall()
{
  if( isFalling == true )
  {
    fBird->setPositionX(visibleSize.width /2 + origin.x);
    fBird->setPositionY(fBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
  }
  
  else
  {
    fBird->setPositionX(visibleSize.width /2 + origin.x);
    fBird->setPositionY(fBird->getPositionY() + (BIRD_FALLING_SPEED * visibleSize.height));
    
  }
}


