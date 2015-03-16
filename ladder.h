#ifndef __LADDER_H__
#define __LADDER_H__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;


class Ladder : public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Ladder);
	void left(float speed);

	int state;
	int dx;
private:
	
	
};


#endif