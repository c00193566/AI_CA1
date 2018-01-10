#pragma once
#include "GameObject.h"
#include "TextureLoader.h"

class Missile
{
private:
	Texture MissileTexture;
	Sprite MissileSprite;
	Vector2f Position;
	Vector2f Velocity;
	float MaxSpeed;
	float Orientation;
	float TimeAlive;
	const float TimeToDie = 5.0f;
	bool Alive;

public:
	Missile() {};
	Missile(Vector2f StartPosition);
	~Missile() {};
	void Update(unsigned int, Vector2f, Vector2f);
	void Render(RenderSystem*);
	void Pursuit(Vector2f, Vector2f);
	void Seek(Vector2f);
	void Movement();
	void TimeUpdate(unsigned int);
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return MissileSprite; };
	bool getAlive() { return Alive; };
	void setAlive(bool set) { Alive = set; };
};