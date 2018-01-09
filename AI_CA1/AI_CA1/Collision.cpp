#include "Collision.h"

void Collision::PlayerCollision(GameObject * Obj, Player * PlayerObj)
{
	if (Obj->getSprite().getGlobalBounds().intersects(PlayerObj->getSprite().getGlobalBounds()))
	{
		PlayerObj->Collision(Obj->getType());
	}
}

void Collision::BulletWallCollision(GameObject * Wall, Bullet * BulletObj)
{
	if (Wall->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
	{
		BulletObj->Dead();
	}
}