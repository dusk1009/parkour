#include "StartScene.h"
#include "GameScene.h"
using namespace cocos2d;

CCScene* StartScene::scene()
{
	CCScene *scene = CCScene::create();
	StartScene *layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCLabelTTF *startLabel = CCLabelTTF::create("Start", "Arial", 50);
	//CCLabelTTF *quitLabel = CCLabelTTF::create("Quit", "Arial", 40);
	CCMenuItemLabel *startMenu = CCMenuItemLabel::create(startLabel, this, menu_selector(StartScene::start));
	//CCMenuItemLabel *quitMenu = CCMenuItemLabel::create(quitLabel, this, menu_selector(StartScene::quit));
	CCMenu *menu = CCMenu::create(startMenu, NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu,1);
	return true;
}

void StartScene::start(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

//void StartScene::quit(CCObject* pSender)
//{
//	CCDirector::sharedDirector()->end();
//}