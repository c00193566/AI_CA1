#pragma once
#include "stdafx.h"
#include "GameObject.h"

class AlienNest : public GameObject
{
private:
	Texture AlienNestTexture;
	Sprite AlienNestSprite;
	Vector2f Position;
	float Range;
	bool PlayerFound;
	bool MissileExists;
	Vector2f MissileDirection;
	bool Culled;

public:
	AlienNest();
	AlienNest(string Tag, Texture & LoadedTexture, float x, float y);
	~AlienNest();
	void Render(RenderSystem *);
	void Update(unsigned int);
	Sprite getSprite() { return AlienNestSprite; };
	string getType() { return Type; };
	Vector2f getPosition() { return Position; };
	bool getCulled() { return Culled; }
	bool setCulled(bool cul) { Culled = cul; }
	void FindPlayer(Vector2f);
	void FireMissile(Vector2f);
};
