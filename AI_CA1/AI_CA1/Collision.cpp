#include "Collision.h"

void Collision::WallCollision(GameObject * Wall, Player * PlayerObj)
{
	if (Wall->getSprite().getGlobalBounds().intersects(PlayerObj->getSprite().getGlobalBounds()))
	{
		PlayerObj->Collision(Wall->getType());
	}
}