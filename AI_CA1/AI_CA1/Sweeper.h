#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Graph.h"
#include "Path.h"
#include "Enemy.h"
#include "Worker.h"

class Sweeper : public GameObject
{
private:
	enum class States
	{
		Setup,
		Search,
		FollowPath,
		FollowWorker
	};

	States CurrentState;
	Texture SweeperTexture;
	Sprite SweeperSprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	float Rotation;
	Vector2f Target;
	int Start;
	int End;
	float MaxRange;
	float MinRange;
	int Lives;
	bool Alive;
	vector<Node*> Path;
	Worker * WorkerTarget;

public:
	Sweeper();
	Sweeper(string Tag, Texture & LoadedTexture, float x, float y);
	~Sweeper();
	void Render(RenderSystem *);
	void Update(unsigned int, Graph<pair<string, int>, int>*, vector<Vector2f>*, vector<Worker*>*);
	void Seek();
	void Movement();
	Sprite getSprite() { return SweeperSprite; };
	string getType() { return Type; };
	Vector2f getPosition() { return Position; };
	bool getAlive() { return Alive; };
	bool CheckBounds();
	void DecreaseLives();
};
