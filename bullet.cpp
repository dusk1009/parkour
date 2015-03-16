#include "bullet.h"

bool Bullet::init()
{
	this->state = Entity_State::NORMOL;
	return true;
}

void Bullet::left(float speed)
{

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
		float posY = rand() % 640;
		this->getSprite()->setPosition(ccp(1300, posY));
		this->state = Entity_State::NORMOL;
	}
}
