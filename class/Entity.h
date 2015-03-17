#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
USING_NS_CC;

enum Entity_State
{
	NORMOL,
	SPRINT,
	OVER
};


class Entity : public CCNode
{
public:
	Entity();
	~Entity();
	CCSprite* getSprite();
	void setSprite(CCSprite* sprite);
	bool isCollideWithEntity(Entity* entity);
private:
	CCSprite *m_sprite;
};

#endif