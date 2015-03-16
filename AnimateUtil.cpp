#include "AnimateUtil.h"

CCAnimate* AnimateUtil::createWithName(char* name, float delay, int loops)
{
	CCSpriteFrameCache *framCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	framCache->addSpriteFramesWithFile(CCString::createWithFormat("%s.plist", name)->getCString(), CCString::createWithFormat("%s.png", name)->getCString());
	CCSpriteFrame *fram = NULL;
	CCArray *framArray = CCArray::create();
	int index = 1;
	do
	{
		fram = framCache->spriteFrameByName(CCString::createWithFormat("%s00%d.png",name, index++)->getCString());
		if (!fram)
			break;
		framArray->addObject(fram);
	} while (true);
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(framArray, delay);
	animation->setLoops(loops);
	return CCAnimate::create(animation);
}