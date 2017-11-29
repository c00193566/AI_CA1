#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class Node
{
private:
	Vector2f Position;
	bool ContainsObject;

public:
	Node(Vector2f P)
	{
		Position = P;
		ContainsObject = false;
	};

	~Node() {};

	void Update(Vector2f ObjPosition)
	{
		if (Position == Vector2f(ObjPosition.x, ObjPosition.y))
		{
			ContainsObject = true;
		}
		else
		{
			ContainsObject = false;
		}
	}

	Vector2f getPosition() { return Position; };

	bool Occupied() { return ContainsObject; };
};