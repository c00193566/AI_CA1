#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "AlienNest.h"
#include "Worker.h"
#include "Sweeper.h"

static struct Collision
{
	static void PlayerCollision(GameObject*, Player*);
	static void BulletWallCollision(vector<Basic*>, Bullet*);
	static void BulletEnemy(vector<Enemy*>, Bullet*);
	static void BulletSweeper(vector<Sweeper*>, Bullet*);
	static void BulletNest(vector<AlienNest*>, Bullet*);
	static void SweeperWorker(GameObject*, vector<Worker*>);
};