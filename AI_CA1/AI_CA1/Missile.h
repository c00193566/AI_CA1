#pragma once
#include "GameObject.h"

class Missile : public GameObject
{
private:
	Texture MissileTexture;
	Sprite MissileSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	Vector2f TargetPosition;

public:
	Missile();
	~Missile();
	void Update(unsigned int);
	void Render(RenderSystem*);
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return MissileSprite; };
	string getType() { return Type; };
};