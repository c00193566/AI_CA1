#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Path.h"

class Worker : public GameObject
{
	enum class States
	{
		Setup,
		Search,
		FollowPath
	};

	States CurrentState;
	Texture WorkerTexture;
	Sprite WorkerSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	float Rotation;
	Vector2f Target;
	int Start;
	int End;

	bool Alive;
	vector<Node*> Path;

public:
	Worker();
	Worker(string Tag, Texture & LoadedTexture, float x, float y);
	~Worker();
	void Render(RenderSystem *);
	void Update(unsigned int, Graph<pair<string, int>, int>*, vector<Vector2f>*);
	void Movement();
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return WorkerSprite; };
	string getType() { return Type; };
	bool CheckBounds();
	void Seek();
	void setAlive(bool set) { Alive = set; };
	bool getAlive() { return Alive; };
	void OrientationToVelocity();
	void Repulsion(vector<Worker*>);
	void Repulsion(vector<Enemy*>);
};