#pragma once
#include "stdafx.h"
#include "RenderSystem.h"

using namespace sf;

static struct Vector
{
	static float Length(Vector2f v)
	{
		float VectorLength = sqrtf(pow(v.x, 2) + pow(v.y, 2));

		return VectorLength;
	};

	static Vector2f Normalise(Vector2f v)
	{
		float length = Length(v);

		if (length > 0)
		{
			Vector2f VectorNormal = Vector2f(v.x / length, v.y / length);
			return VectorNormal;
		}
		else
		{
			return Vector2f(0, 0);
		}
	};

	static float GetOrientation(float CurrentOrientation, Vector2f Velocity)
	{
		float rotation = CurrentOrientation;

		if (Length(Velocity) > 0)
		{
			rotation = atan2f(Velocity.x, -Velocity.y);

			rotation = RadsToDegs(rotation);
		}

		return rotation;
	}

	static float RadsToDegs(float Rads)
	{
		float degs = Rads * 180 / 3.14;

		return degs;
	}
};

class GameObject
{
public:
	virtual void Render(RenderSystem *) = 0;
	virtual Sprite getSprite() = 0;
	virtual string getType() = 0;
	virtual Vector2f getPosition() = 0;

protected:
	string Type;
};