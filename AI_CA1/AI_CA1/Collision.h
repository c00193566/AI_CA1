#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"

static struct Collision
{
	static void WallCollision(GameObject*, Player*);
};