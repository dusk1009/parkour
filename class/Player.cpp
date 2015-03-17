#include "Player.h"
#include "OverScene.h"

Player::Player()
{

}
Player::~Player()
{

}
bool Player::init()
{
	m_score = 0;
	dy = 0;
	state = Player_State::DOWN;
	jumpTimes = 2;
	sprintTimes = 1;
	return true;
}

void Player::jump()
{
	//if (!m_isJumping)
	//{
	//	m_isJumping = true;
	//	CCJumpBy *m_actionJump = CCJumpTo::create(0.5f, ccp(320, 0), 150, 1);
	//	CCAction *callFunc = CCCallFunc::create(this, callfunc_selector(Player::jumpEnd));
	//	CCAction *jumpActions = CCSequence::create(m_actionJump, callFunc, NULL);
	//	jumpActions->setTag(0);
	//	getSprite()->runAction(jumpActions);
	//}
	if (state == Player_State::UP)
	{
		getSprite()->setPositionY(getSprite()->getPositionY() + dy);
		dy -= 2;
		if (dy <= 0)
		{
			state = Player_State::DOWN;
		}
	}
	else if (state == Player_State::DOWN)
	{
		dy += 2;
		getSprite()->setPositionY(getSprite()->getPositionY() - dy);
	}
	else if (state == Player_State::STOP)
	{
		jumpTimes = 2;
		sprintTimes = 1;
		dy = 0;
	}
	else if (state == Player_State::SPRINT)
	{
		dy = 0;
		state = Player_State::DOWN;
	}
	else if (state == Player_State::OVER)
	{
		CCDirector::sharedDirector()->replaceScene(OverScene::scene(m_score));
	}
	
}
