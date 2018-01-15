#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Graph.h"
#include "Path.h"
#include "Enemy.h"

class Sweeper : public GameObject
{
private:
	enum class States
	{
		Setup,
		Search,
		FollowPath
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

	bool Alive;
	vector<Node*> Path;

public:
	Sweeper();
	Sweeper(string Tag, Texture & LoadedTexture, float x, float y);
	~Sweeper();
	void Render(RenderSystem *);
	void Update(unsigned int, Graph<pair<string, int>, int>*, vector<Vector2f>*, vector<Enemy*>*);
	void Seek();
	void Movement();
	Sprite getSprite() { return SweeperSprite; };
	string getType() { return Type; };
	Vector2f getPosition() { return Position; };
	bool CheckBounds();
};
