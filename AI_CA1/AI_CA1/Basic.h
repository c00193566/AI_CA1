#pragma once
#include "GameObject.h"

class Basic : public GameObject
{
private:
	Texture BasicTexture;
	Sprite BasicSprite;
	Vector2f Position;

public:
	Basic() {};
	Basic(string Tag, Texture & LoadedTexture, float x, float y);
	~Basic();
	void Render(RenderSystem *);
	void Update(unsigned int);
	Sprite getSprite() { return BasicSprite; };
	string getType() { return Type; };
	Vector2f getPosition() { return Position; };
};