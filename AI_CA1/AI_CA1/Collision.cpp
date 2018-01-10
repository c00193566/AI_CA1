#include "Collision.h"
#include "AlienNest.h"

void Collision::PlayerCollision(GameObject * Obj, Player * PlayerObj)
{
	if (Obj->getSprite().getGlobalBounds().intersects(PlayerObj->getSprite().getGlobalBounds()))
	{
		PlayerObj->Collision(Obj->getType());
	}

	if (Obj->getType() == "AlienNest")
	{
		AlienNest * AlienObj = static_cast<AlienNest*>(Obj);
		for (int i = 0; i < AlienObj->getMissiles().size(); i++)
		{
			if (AlienObj->getMissiles().at(i)->getSprite().getGlobalBounds().intersects(PlayerObj->getSprite().getGlobalBounds()))
			{
				AlienObj->getMissiles().at(i)->setAlive(false);
				PlayerObj->Collision("Missile");
			}
		}
	}
}

void Collision::BulletWallCollision(GameObject * Wall, Bullet * BulletObj)
{
	if (Wall->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
	{
		BulletObj->Dead();
	}
}