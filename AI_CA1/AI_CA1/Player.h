#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	Texture PlayerTexture;
	Sprite PlayerSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	float Friction;

	float MaxSpeed = 5.0f;
	float MinSpeed = 0.0f;

public:
	Player();
	~Player();
	bool Init(string Tag, string path, Vector2f position);
	bool Init(string Tag, string path, float x, float y);
	void Render(RenderSystem *);
	void Update(unsigned int);
	void Movement();
	void Input(string);
	void SetVelocity();
	void Collision(string ObjType);
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return PlayerSprite; };
	string getType() { return Type; };
};