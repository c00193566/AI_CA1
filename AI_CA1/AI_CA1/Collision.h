#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"

static struct Collision
{
	static void PlayerCollision(GameObject*, Player*);
	static void BulletWallCollision(GameObject*, Bullet*);
};