#include "CCLayerParent.h"
#include "Scenes.h"

USING_NS_CC;
CCLayerParent::CCLayerParent()
{
	
}

void CCLayerParent::basicSetup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float MARGIN = 26 / CC_CONTENT_SCALE_FACTOR();

	//nodes
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
	_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
	this->addChild(_batchNodes);
	_particleNodes = CCDictionary::create();
	_particleNodes->setObject(CCParticleBatchNode::create("bullet.png"),"bullet");
	_particleNodes->setObject(CCParticleBatchNode::create("explosion1.png"),"explosion1");
	_particleNodes->setObject(CCParticleBatchNode::create("explosion2.png"),"explosion2");
	_particleNodes->setObject(CCParticleBatchNode::create("aoe1.png"),"aoe1");
	_particleNodes->setObject(CCParticleBatchNode::create("aoe2.png"),"aoe2");
	CCDictElement* object = NULL;
	CCDICT_FOREACH(_particleNodes,object)
	{
		this->addChild((CCParticleBatchNode*)object->getObject());
	}


   // Sounds
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Latin_Industries.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("bigHit.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew2.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("smallHit.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("attack.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("defend.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("spawn.wav");

	//other UI
	CCSprite *background = CCSprite::create("background.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background,-1);
    
    quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(CCLayerParent::quirkButtonTapped));
    zapButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(CCLayerParent::zapButtonTapped));
    munchButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(CCLayerParent::munchButtonTapped));

	CCSize contentSize =  zapButton->getContentSize();
    zapButton->setPosition (ccp(winSize.width/2, MARGIN + contentSize.height/2));
    quirkButton->setPosition (ccp(zapButton->getPosition().x - contentSize.width/2 - MARGIN - contentSize.width/2, MARGIN + contentSize.height/2));
    munchButton->setPosition ( ccp(zapButton->getPosition().x + contentSize.width/2 + MARGIN + contentSize.width/2, MARGIN + contentSize.height/2));
    
    CCSprite* quirk = CCSprite::createWithSpriteFrameName("quirk1.png");
    quirk->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    quirkButton->addChild(quirk);
    
    CCSprite* zap = CCSprite::createWithSpriteFrameName("zap1.png");
    zap->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    zapButton->addChild(zap);
    
    CCSprite* munch = CCSprite::createWithSpriteFrameName("munch1.png");
    munch->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    munchButton->addChild(munch);

    char temp[64];
    sprintf(temp, "%d", COST_QUIRK);

    CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");

    quirkLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.0));
    quirkButton->addChild(quirkLabel);
	
	sprintf(temp, "%d", COST_ZAP);

    CCLabelBMFont* zapLabel = CCLabelBMFont::create(temp,"Courier.fnt");
    zapLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.0));
    zapButton->addChild(zapLabel);

	sprintf(temp, "%d", COST_MUNCH);

    CCLabelBMFont* munchLabel = CCLabelBMFont::create(temp,"Courier.fnt");
    munchLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.0));
    munchButton->addChild(munchLabel);


    _stateLabel = CCLabelBMFont::create("Idle","Courier.fnt");
    _stateLabel->setPosition ( ccp(winSize.width/2, winSize.height * 0.3));
    this->addChild(_stateLabel);
    
    menu = CCMenu::create(quirkButton, zapButton, munchButton, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    CCSprite* coin1 = CCSprite::createWithSpriteFrameName("coin.png");

    contentSize = coin1->getContentSize();
    coin1->setPosition(ccp(MARGIN + contentSize.width/2, winSize.height - MARGIN - contentSize.height/2));
    this->addChild(coin1);
    
    CCSprite* coin2 = CCSprite::createWithSpriteFrameName("coin.png");
    coin2->setPosition(ccp(winSize.width - MARGIN - contentSize.width/2, winSize.height - MARGIN - contentSize.height/2));;
    this->addChild(coin2);
        
    _coin1Label = CCLabelBMFont::create("10","Courier.fnt",winSize.width * 0.25,kCCTextAlignmentLeft);
    _coin1Label->setPosition(ccp(coin1->getPosition().x + contentSize.width/2 + MARGIN/2 + _coin1Label->getContentSize().width/2, winSize.height - MARGIN*1.5));
    this->addChild(_coin1Label);
    
    _coin2Label = CCLabelBMFont::create("10","Courier.fnt",winSize.width * 0.25,kCCTextAlignmentRight);;
    _coin2Label->setPosition ( ccp(coin2->getPosition().x -  contentSize.width/2 - MARGIN/2 - _coin1Label->getContentSize().width/2, winSize.height - MARGIN*1.5));
    this->addChild(_coin2Label);
    
    this->setTouchEnabled(true);
    this->scheduleUpdate();
	_gameOver=false;
	
}
void CCLayerParent::addPlayers()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_entityManager =new EntityManager();
	_entityFactory = new EntityFactory(_entityManager,_batchNodes);
	CCDictElement* object = NULL;
	CCDICT_FOREACH(_particleNodes,object)
	{
		_entityFactory->AddBatchNode((CCParticleBatchNode*)object->getObject(),object->getStrKey());
	}
	

	_healthSystem =new HealthSystem(_entityManager,_entityFactory);
	_moveSystem =new MoveSystem(_entityManager,_entityFactory);
	_playerSystem = new PlayerSystem(_entityManager,_entityFactory);
	_meleeSystem = new MeleeSystem(_entityManager,_entityFactory);
	_gunSystem = new GunSystem(_entityManager,_entityFactory);
	_aiSystem = new AISystem(_entityManager,_entityFactory);
	//_physicsSystem = new PhysicsSystem(_entityManager,_entityFactory,_world);
	
    _aiPlayer = _entityFactory->createAIPlayer();
	_aiPlayer->retain();
    RenderComponent* aiRender =  _aiPlayer->render();
	if (aiRender) {
        aiRender->node->setPosition ( ccp(winSize.width - aiRender->node->getContentSize().width/2, winSize.height/2));
        aiRender->node->setZOrder(-1);
	}
	
    _humanPlayer = _entityFactory->createHumanPlayer();
	_humanPlayer->retain();
    RenderComponent* humanRender =_humanPlayer->render();
    if (humanRender) {
        humanRender->node->setPosition ( ccp(humanRender->node->getContentSize().width/2, winSize.height/2));
        humanRender->node->setZOrder(-1);
    }  
	
   
}

void CCLayerParent::quirkButtonTapped(CCObject* obj) {    
   CCLog("Quirk button tapped!");

     PlayerComponent* humanPlayer = _humanPlayer->player();
    if (!humanPlayer) return;    
    if (humanPlayer->coins < COST_QUIRK) return;
    humanPlayer->coins -= COST_QUIRK;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    for (int i = 0; i < 2; ++i) {

	    Entity* entity = _entityFactory->createQuirkMonsterWithTeam(1);
	    RenderComponent* render =entity->render();
	    if (render) {        
	        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	        float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
	        render->node->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
			
		}
		

   	}
}

void CCLayerParent::zapButtonTapped(CCObject* obj)  {
      CCLog("Zap button tapped!");

     PlayerComponent* humanPlayer = _humanPlayer->player();
    if (!humanPlayer) return;    
    if (humanPlayer->coins < COST_ZAP) return;
    humanPlayer->coins -= COST_ZAP;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
    Entity* entity = _entityFactory->createZapMonsterWithTeam(1);
    RenderComponent* render =entity->render();
    if (render) {        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
        render->node->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
    	
	}
}

void CCLayerParent::munchButtonTapped(CCObject* obj)  {
    CCLog("Munch button tapped!");

     PlayerComponent* humanPlayer = _humanPlayer->player();
    if (!humanPlayer) return;    
    if (humanPlayer->coins < COST_MUNCH) return;
    humanPlayer->coins -= COST_MUNCH;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
    Entity* entity = _entityFactory->createMunchMonsterWithTeam(1);
    RenderComponent* render =entity->render();
    if (render) {        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
        render->node->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
		
	}
}



void CCLayerParent::restartTapped(CCObject* obj){
    
    // Reload the current scene
    CCScene *scene = ArmorHome::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipX::create(0.5,scene));
    
}

void CCLayerParent::showRestartMenu(bool won) {
     if (_gameOver) return;
    _gameOver = true;
	
	CCScene *scene = GameOverLayer::scene(won,1);
    CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipX::create(0.5,scene));
    /*
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCString *message;
    if (won) {
        message = ccs("You win!");
    } else {
        message = ccs("You lose!");
    }
    
    CCLabelBMFont* label = CCLabelBMFont::create(message->getCString(),"Courier.fnt");

    label->setScale ( 0.1f);
    label->setPosition ( ccp(winSize.width/2, winSize.height * 0.6));
    this->addChild(label);
    
    CCLabelBMFont *restartLabel =CCLabelBMFont::create("Restart" ,"Courier.fnt");
    
    
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel,this,menu_selector(CCLayerParent::restartTapped));
    restartItem->setScale ( 0.1f);
    restartItem->setPosition ( ccp(winSize.width/2, winSize.height * 0.4));
    
    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition (CCPointZero);
	this->addChild(menu,10);

    
    restartItem->runAction(CCScaleTo::create(0.5,1.0));
    label->runAction(CCScaleTo::create(0.5,1.0));
    */
}


void CCLayerParent::update(float delta){
    _healthSystem->update(delta);
	_moveSystem->update(delta);
	_playerSystem->update(delta);
	_meleeSystem->update(delta);
	_gunSystem->update(delta);
	_aiSystem->update(delta);
	//_physicsSystem->update(delta);
	
    // Check for game over
    HealthComponent* humanHealth = _humanPlayer->health();
    if (humanHealth) {
        if (humanHealth->curHP <= 0) {
            this->showRestartMenu(false);
        }
    }    
    HealthComponent* aiHealth = _aiPlayer->health();
    if (aiHealth) {
        if (aiHealth->curHP <= 0) {
           this->showRestartMenu(true);
        }
    }
    
    // Display coins
    PlayerComponent* humanPlayer = _humanPlayer->player();
    if (humanPlayer) {
        _coin1Label->setString(CCString::createWithFormat("%d", humanPlayer->coins)->getCString());
    }
    PlayerComponent* aiPlayer = _aiPlayer->player();
    if (aiPlayer) {
        _coin2Label->setString(CCString::createWithFormat("%d", aiPlayer->coins)->getCString());
    }
    
    // Display AI state
    AIComponent* aiComp = _aiPlayer->ai();
    if (aiComp) {
        _stateLabel->setString(aiComp->state->name()->getCString());
    }
    
}

void CCLayerParent::draw(){
    _healthSystem->draw();
}
void CCLayerParent::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool CCLayerParent::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    CCLog("Touch at: %f,%f",touchPoint.x,touchPoint.y);
    
    RenderComponent* render = _humanPlayer->render();
    PlayerComponent* player = _humanPlayer->player();
    if (render && player) {
        if (render->node->boundingBox().containsPoint(touchPoint)) {
            player->attacking = !player->attacking;
        }
    }
	return true;
}

void CCLayerParent::release()
{
	CCLayer::release();
	_humanPlayer->release();
	_aiPlayer->release();
	delete _entityManager;  
	delete _entityFactory; 

	delete _healthSystem; 
	delete _moveSystem; 
	delete _playerSystem; 
	delete _meleeSystem;  
	delete _gunSystem; 
	//delete _physicsSystem;
}
