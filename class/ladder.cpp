#include "ladder.h"

bool Ladder::init()
{
	state = Entity_State::NORMOL;
	return true;
}

void Ladder::left(float speed)
{
	//CCMoveBy *aLeft = CCMoveBy::create(speed, ccp(-1500, 0));
	//CCAction *callFunc = CCCallFunc::create(this, callfunc_selector(Ladder::leftEnd));
	//CCAction *leftActions = CCSequence::create(aLeft, callFunc, NULL);
	//getSprite()->runAction(leftActions);

	if (this->state == Entity_State::NORMOL)
	{
		this->getSprite()->setPositionX(this->getSprite()->getPositionX() - speed);
		if (this->getSprite()->getPositionX() < -200)
			this->state = Entity_State::OVER;
	}
	else if (this->state == Entity_State::SPRINT)
	{
		this->getSprite()->setPositionX(this->getSprite()->getPositionX() - speed - dx);
		dx -= 2;
		if (dx <= 0)
			this->state = Entity_State::NORMOL;
	}
	else if (this->state == Entity_State::OVER)
	{
		float posY = rand() % 400;
		float posX = rand() % 300;
		this->getSprite()->setPosition(ccp(1300+posX, posY));
		this->state = Entity_State::NORMOL;
	}
}
