#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Node.h"

class Worker : public GameObject
{
	Texture WorkerTexture;
	Sprite WorkerSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	Vector2f Target;
	bool TargetReached;
	bool TargetFound;

public:
	Worker();
	Worker(string Tag, Texture & LoadedTexture, float x, float y);
	~Worker();
	void Render(RenderSystem *);
	void Update(unsigned int);
	void Movement();
	void FindTarget(vector<Node*> Nodes);
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return WorkerSprite; };
	string getType() { return Type; };
};