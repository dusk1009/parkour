#include "Entity.h"

Entity::Entity()
{
	m_sprite = NULL;
}

Entity::~Entity()
{
	//m_sprite->release();
}

CCSprite* Entity::getSprite()
{
	return this->m_sprite;
}

void Entity::setSprite(CCSprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);
}

//CCRect Entity::getBoundingBox()
//{
//	if (!getSprite())
//		return CCRectMake(0, 0, 0, 0);
//	CCSize size = getSprite()->getContentSize();
//	CCPoint pos = getSprite()->getPosition();
//	CCLOG("%f,%f,%f,%f", pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
//	return CCRectMake(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
//}

bool Entity::isCollideWithEntity(Entity* entity)
{
	return this->getSprite()->boundingBox().intersectsRect(entity->getSprite()->boundingBox());
}
