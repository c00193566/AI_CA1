#include "Collision.h"

void Collision::PlayerCollision(GameObject * Obj, Player * PlayerObj)
{
	if (Obj->getSprite().getGlobalBounds().intersects(PlayerObj->getSprite().getGlobalBounds()))
	{
		PlayerObj->Collision(Obj->getType());

		if (Obj->getType() == "Worker")
		{
			Worker * WorkerObj = static_cast<Worker*>(Obj);
			WorkerObj->setAlive(false);
		}
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

void Collision::BulletWallCollision(vector<Basic*> Walls, Bullet * BulletObj)
{
	if (Walls.size() > 0)
	{
		for (int i = 0; i < Walls.size(); i++)
		{
			if (Walls.at(i)->getType() != "Walkway")
			{
				if (Walls.at(i)->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
				{
					BulletObj->Dead();
				}
			}
		}
	}
}

void Collision::BulletEnemy(vector<Enemy*> Enemies, Bullet * BulletObj)
{
	if (Enemies.size() > 0)
	{
		for (int i = 0; i < Enemies.size(); i++)
		{
			if (Enemies.at(i)->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
			{
				BulletObj->Dead();
				Enemies.at(i)->DecreaseLives();
			}
		}
	}
}

void Collision::BulletSweeper(vector<Sweeper*> Boid, Bullet * BulletObj)
{
	if (Boid.size() > 0)
	{
		for (int i = 0; i < Boid.size(); i++)
		{
			if (Boid.at(i)->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
			{
				BulletObj->Dead();
				Boid.at(i)->DecreaseLives();
			}
		}
	}
}

void Collision::BulletNest(vector<AlienNest*> Boid, Bullet * BulletObj)
{
	if (Boid.size() > 0)
	{
		for (int i = 0; i < Boid.size(); i++)
		{
			if (Boid.at(i)->getSprite().getGlobalBounds().intersects(BulletObj->getSprite().getGlobalBounds()))
			{
				BulletObj->Dead();
			}
		}
	}
}

void Collision::SweeperWorker(GameObject * Boid, vector<Worker*> WorkerObjs)
{
	for (int i = 0; i < WorkerObjs.size(); i++)
	{
		if (Boid->getSprite().getGlobalBounds().intersects(WorkerObjs.at(i)->getSprite().getGlobalBounds()))
		{
			WorkerObjs.at(i)->setAlive(false);
			break;
		}
	}
}