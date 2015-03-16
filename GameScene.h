#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Player.h"
#include "ladder.h"
#include "bullet.h"
#include "AnimateUtil.h"
USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
	
	
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	bool initbackGround();
	bool initMenu();
	bool initPlayer();
	bool createScoreLab();
	bool createBullet();
	bool createLadder(CCPoint pos);

	void menuSprintCallback(CCObject* pSender);
	void menuJumpCallback(CCObject* pSender);

	virtual void update(float delta);
	void speedUp(float delta);

	Player *m_player;
	Bullet *m_bullet;
	Ladder *m_ladder;	
	CCArray *ladderArray;
	CCLabelTTF *m_scoreLab;
	CCSize visibleSize;
	int m_score;
	float m_ladderSpeed;
	float m_bulletSpeed;
	bool isTouching;
};

#endif
