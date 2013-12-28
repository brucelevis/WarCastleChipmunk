
#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
CCScene* Splash::scene()
{
	CCScene *scene = CCScene::create();

	Splash *splash = Splash::create();

	scene->addChild(splash);

	return scene;

}


void Splash::gameLogic(float dt)
{
	this->addMonster();
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool Splash::init()
{
	if(! CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("140481__roigianno__opening-scene.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fullPath.c_str());
	_monsters = CCArray::create();
	_projectiles = CCArray::create();
	_monsters->retain();
	_projectiles->retain();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_player = CCSprite::create("player2.png");
	_player->setPosition(ccp(_player->getContentSize().width/2,winSize.height/2));
	this->addChild(_player);

	this->schedule(schedule_selector(Splash::gameLogic),1.0);
	this->schedule(schedule_selector(Splash::update));

	this->setTouchEnabled(true);

	_monstersDestroyed = 0;
	return true;
}

void Splash::addMonster()
{
	CCSprite *monster = CCSprite::create("monster.png");
	monster->setTag(1);
	_monsters->addObject(monster);
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = monster->getTextureRect().size.height;
	int maxY = winSize.height- minY;
	int range = maxY-minY;
	int acturalY = minY+ (rand()%maxY);
	monster->setPosition(ccp(winSize.width+monster->getContentSize().width,acturalY));
	this->addChild(monster);

	int minDuration = 2.0f;
	int maxDuration = 4.0f;
	int rangeDuration = maxDuration- minDuration;
	int acturalDuration = minDuration + (rand() % maxDuration);

	CCMoveTo *actionMove = CCMoveTo::create(acturalDuration,ccp(-monster->getContentSize().width,acturalY));
	CCCallFuncN *actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(Splash::monsterMoveEnded));
	monster->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
	
 }


void Splash::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool Splash::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void Splash::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//if(_nextProjectile!=NULL) return;
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("pew-pew-lei.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(fullPath.c_str());

	CCPoint position = this->convertTouchToNodeSpace(pTouch);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	_nextProjectile = CCSprite::create("projectile2.png");
	_nextProjectile->retain();
	_nextProjectile ->setTag(2);
	//_projectiles->addObject(_nextProjectile );
	
	_nextProjectile ->setPosition(ccp(20,winSize.height/2));
	
	float bearVelocity = winSize.width / 1.0;
	CCPoint moveDifference = ccpSub(position,_nextProjectile->getPosition());
	if(moveDifference.x<0) return;
	//this->addChild(_nextProjectile);
	
	int realX = winSize.width + _nextProjectile ->getContentSize().width/2;
	float ratio = (float)moveDifference.y/moveDifference.x;
	int realY = (realX * ratio) + _nextProjectile ->getPosition().y;

	CCPoint realDest = ccp(realX,realY);
	CCPoint realDistance = ccpSub(realDest,_nextProjectile ->getPosition());
	
	float distanceToMove = ccpLength(realDistance);
	float moveDuration = distanceToMove / bearVelocity;

	float angleRadius = atanf(realDistance.y/realDistance.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadius);
	float cocosDegrees = - angleDegrees;
	float rotateDegreesPerSecond = 180 / 0.5f;
	float degreesDiff = _player->getRotation() - cocosDegrees;
	float rotateDuration = fabs(degreesDiff / rotateDegreesPerSecond);

	_player->runAction(CCSequence::create(CCRotateTo::create(rotateDuration,cocosDegrees),
		CCCallFuncN::create(this,callfuncN_selector(Splash::playerMoveEnded)),
		NULL));
	_player->setRotation(cocosDegrees);
	_nextProjectile ->runAction(CCSequence::create(CCMoveTo::create(moveDuration,realDest),
		CCCallFuncN::create(this,callfuncN_selector(Splash::MoveEnded)),
		NULL));

}

void Splash::update(float dt)
{
	CCArray *projectileToDelete = CCArray::create();
	CCObject *pit=NULL;
	CCARRAY_FOREACH(_projectiles,pit)
	{
		CCArray *monstersToDelete = CCArray::create();
		CCObject* mit = NULL;
		CCARRAY_FOREACH(_monsters,mit)
		{
			if(dynamic_cast<CCSprite*>(pit)->boundingBox().intersectsRect(dynamic_cast<CCSprite*>(mit)->boundingBox()))
			{
				monstersToDelete ->addObject(mit);
			}
		}

		CCARRAY_FOREACH(monstersToDelete, mit)
		{
			_monsters->removeObject(mit);
			this->removeChild(dynamic_cast<CCSprite*>(mit),true);
			_monstersDestroyed++;
			if(_monstersDestroyed>30)
			{
				CCScene *gameover = GameOverLayer::scene(true,1);
				CCDirector::sharedDirector()->replaceScene(gameover);
			}
		}

		if(monstersToDelete->count())
			projectileToDelete->addObject(dynamic_cast<CCSprite*>(pit));

		monstersToDelete->release();
		
		CCARRAY_FOREACH(projectileToDelete,pit)
		{
			_projectiles->removeObject(pit);
			this->removeChild(dynamic_cast<CCSprite*>(pit),true);

		}
	}
	projectileToDelete->release();
}
