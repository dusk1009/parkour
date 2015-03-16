#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "cocos2d.h"

class StartScene : public cocos2d::CCLayer
{
public:

	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(StartScene);

private:

	void menuStartCallback(CCObject* pSender);
	void start(CCObject* pSender);
	//void quit(CCObject* pSender);
};
#endif