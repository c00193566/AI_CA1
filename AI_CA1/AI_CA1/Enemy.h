#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include <queue>

class Enemy : public GameObject
{
	Texture WorkerTexture;
	Sprite WorkerSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	Vector2f Target;
	bool Wander;
	float Range;
	vector<Vector2f> path;

public:
	Enemy();
	Enemy(string Tag, Texture & LoadedTexture, float x, float y);
	~Enemy();
	void Render(RenderSystem *);
	void Update(unsigned int);
	void Movement();
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return WorkerSprite; };
	string getType() { return Type; };
	bool getCulled() { return Culling; };
	void setCulled(bool set) { Culling = set; };
};