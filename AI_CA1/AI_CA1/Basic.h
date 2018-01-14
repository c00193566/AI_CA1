#pragma once
#include "GameObject.h"

class Basic : public GameObject
{
private:
	Texture BasicTexture;
	Sprite BasicSprite;
	Vector2f Position;
	bool Culling;

public:
	Basic() {};
	Basic(string Tag, Texture & LoadedTexture, float x, float y);
	~Basic();
	void Render(RenderSystem *);
	Sprite getSprite() { return BasicSprite; };
	string getType() { return Type; };
	Vector2f getPosition() { return Position; };
};