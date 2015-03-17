#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;


class Bullet : public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	void left(float speed);

	int state;
	int dx;
private:
};


#endif