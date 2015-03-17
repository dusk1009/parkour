#include "GameScene.h"
#include "OverScene.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_ladderSpeed = 5;
	m_bulletSpeed = 10;
	
	initbackGround();
	initMenu();
	initPlayer();
	createScoreLab();
	

	ladderArray = CCArray::createWithCapacity(4); 
	ladderArray->retain();
	createLadder(ccp(350, 100));
	createLadder(ccp(650, 50));
	createLadder(ccp(1050, 100));
	createLadder(ccp(1450, 300));

	createBullet();

	this->schedule(schedule_selector(GameScene::speedUp), 2);
	this->scheduleUpdate();
    return true;
}

bool GameScene::initbackGround()
{
	//CCSprite *backGround1 = CCSprite::create("background.png");
	//backGround1->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	//CCAction *move1 = CCMoveBy::create(5.0f, ccp(-visibleSize.width , 0));
	//backGround1->runAction(move1);
	//this->addChild(backGround1,0);

	//CCSprite *backGround2 = CCSprite::create("background.png");
	//backGround2->setPosition(ccp(visibleSize.width * 1.5, visibleSize.height /2));
	//CCAction *move2 = CCMoveBy::create(5.0f, ccp(-visibleSize.width, 0));
	//backGround2->runAction(move2);
	//this->addChild(backGround2,0);

	return true;
}

bool GameScene::initMenu()
{
	CCLabelTTF *sprintLable = CCLabelTTF::create("Sprint", "Arial", 80);
	CCMenuItemLabel *sprintMenuItem = CCMenuItemLabel::create(sprintLable, this, menu_selector(GameScene::menuSprintCallback));
	sprintMenuItem->setAnchorPoint(ccp(0, 0));
	CCMenu *sprintMenu = CCMenu::create(sprintMenuItem, NULL);
	sprintMenu->setPosition(ccp(0, 0));
	this->addChild(sprintMenu,1);

	CCLabelTTF *jumpLable = CCLabelTTF::create("Jump", "Arial", 80);
	CCMenuItemLabel *jumpMenuItem = CCMenuItemLabel::create(jumpLable, this, menu_selector(GameScene::menuJumpCallback));
	jumpMenuItem->setAnchorPoint(ccp(1, 0));
	CCMenu *jumpMenu = CCMenu::create(jumpMenuItem, NULL);
	jumpMenu->setPosition(ccp(visibleSize.width, 0));
	this->addChild(jumpMenu,1);

	return true;
}

bool GameScene::initPlayer()
{
	CCSprite *playerSprite = CCSprite::create();
	m_player = Player::create();
	m_player->setSprite(playerSprite);
	m_player->getSprite()->setPosition(ccp(320, 200));
	CCAnimate *runAnimate = AnimateUtil::createWithName("run", 0.1, -1);
	m_player->getSprite()->runAction(runAnimate);
	this->addChild(m_player);
	return true;
}

bool GameScene::createScoreLab()
{
	m_scoreLab = CCLabelTTF::create("Score:0", "Arial", 30);
	m_scoreLab->setPosition(ccp(0, visibleSize.height));
	m_scoreLab->setAnchorPoint(ccp(0, 1));
	this->addChild(m_scoreLab);
	return true;
}

bool GameScene::createBullet()
{
	CCSprite *bulletSprite = CCSprite::create();
	m_bullet = Bullet::create();
	m_bullet->setSprite(bulletSprite);
	m_bullet->getSprite()->setPosition(ccp(1300, 150));
	CCAnimate *runAnimate = AnimateUtil::createWithName("bullet", 0.1, -1);
	m_bullet->getSprite()->runAction(runAnimate);
	this->addChild(m_bullet);
	return true;
}

bool GameScene::createLadder(CCPoint pos)
{
	CCSprite *ladderSprite = CCSprite::create("ladder.png");
	//ladderSprite->setScaleY(0.3f);
	//ladderSprite->setScaleX(2);
	Ladder *ladder = Ladder::create();
	ladder->setSprite(ladderSprite);
	ladder->getSprite()->setPosition(pos);
	this->addChild(ladder);
	ladderArray->addObject(ladder);
	//CCLOG("%d", ladder->retainCount());
	return true;
}

void GameScene::speedUp(float delta)
{
	m_ladderSpeed += 0.5;
	m_bulletSpeed += 1;
	//CCDirector::sharedDirector()->getScheduler()->setTimeScale(2);
	//this->scheduleOnce(schedule_selector(GameScene::updateLadder), m_ladderSpeed);
}

void GameScene::update(float dt)
{
	do
	{
		//各物体运动
		m_bullet->left(m_bulletSpeed);
		m_player->jump();
		for (int i = 0; i < ladderArray->count(); i++)
		{
			Ladder* ladder = ((Ladder*)ladderArray->objectAtIndex(i));
			ladder->left(m_ladderSpeed);
		}

		//判断是否在加速
		if (m_bullet->state == Entity_State::SPRINT)
			m_player->state = Player_State::SPRINT;

		//撞子弹死亡
		if (m_bullet->isCollideWithEntity(m_player))
		{
			m_player->state = Player_State::OVER;
			break;
		}	
		

		//判断与梯子的碰撞
		isTouching = false;
		if (m_player->state != Player_State::UP)
		{
			for (int i = 0; i < ladderArray->count(); i++)
			{
				if (((Ladder*)ladderArray->objectAtIndex(i))->isCollideWithEntity(m_player))
				{
					isTouching = true;
					m_player->state = Player_State::STOP;
					m_player->getSprite()->setPositionY(((Ladder*)ladderArray->objectAtIndex(i))->getSprite()->getPositionY() + 62.5);
					break;
				}
			}
			if (!isTouching && m_player->state == Player_State::STOP)
			{
				m_player->jumpTimes = 0;
				m_player->state = Player_State::DOWN;
			}
		}

		//掉落死亡
		if (m_player->getSprite()->getPositionY() < -100)
		{
			m_player->state = Player_State::OVER;
			break;
		}

		//刷新分数
		m_player->m_score += 1;
		m_scoreLab->setString(CCString::createWithFormat("Score:%d", m_player->m_score)->getCString());
	} while (0);
}

void GameScene::menuSprintCallback(CCObject* pSender)
{
	if (m_player->sprintTimes > 0)
	{
		m_player->sprintTimes--;
		for (int i = 0; i < ladderArray->count(); i++)
		{
			((Ladder*)ladderArray->objectAtIndex(i))->state = Entity_State::SPRINT;
			((Ladder*)ladderArray->objectAtIndex(i))->dx = 30;
		}
		m_bullet->state = Entity_State::SPRINT;
		m_bullet->dx = 30;
	}

}

void GameScene::menuJumpCallback(CCObject* pSender)
{
	if (m_player->jumpTimes>0)
	{
		m_player->jumpTimes--;
		m_player->dy = 30;
		m_player->state = Player_State::UP;
	}
}