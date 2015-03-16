#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

enum class Player_State
{
	UP,
	DOWN,
	STOP,
	SPRINT,
	OVER
};

class Player : public Entity
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);
	void jump();

	Player_State state;
	int dy;
	int jumpTimes;
	int sprintTimes;
	int m_score;
private:
};


#endif