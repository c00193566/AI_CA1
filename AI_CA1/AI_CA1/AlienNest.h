#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Missile.h"

class AlienNest : public GameObject
{
private:
	Texture AlienNestTexture;
	Sprite AlienNestSprite;
	Vector2f Position;
	float Range;
	const int MaxMissiles = 1;
	bool PlayerFound;
	bool MissileExists;

	vector<Missile*> Missiles;
	float TimeDelay;

public:
	AlienNest();
	AlienNest(string Tag, Texture & LoadedTexture, float x, float y);
	~AlienNest();
	void Render(RenderSystem *);
	void Update(unsigned int);
	Sprite getSprite() { return AlienNestSprite; };
	string getType() { return Type; };
	Vector2f getPosition() { return Position; };
	void UpdateMissileInfo();
	void FindPlayer(Vector2f);
	void FireMissile(Vector2f);
};
