#include "Collision.h"

void Collision::WallCollision(GameObject * Wall, Player * PlayerObj)
{
	if (Wall->getSprite().getGlobalBounds().intersects(PlayerObj->getSprite().getGlobalBounds()))
	{
		PlayerObj->Collision(Wall->getType());
	}
}

void Collision::BulletWallCollision(GameObject * Wall, Bullet * BulletObj)
{
	if (Wall->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
	{
		BulletObj->Dead();
	}
}