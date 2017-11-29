#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Texture BulletTexture;
	Sprite BulletSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float TimeAlive;

	bool Alive;

public:
	Bullet();
	Bullet(string Tag, Texture & LoadedTexture, Vector2f InputPosition, float Direction);
	~Bullet();

	void Render(RenderSystem * Renderer);
	void Update(unsigned int DT);

	void Dead();

	Sprite getSprite() { return BulletSprite; };
	string getType() { return Type; };
	bool getAlive() { return Alive; };
};