#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Path.h"


class Enemy : public GameObject
{
	enum class States
	{
		Search,
		FollowPath,
		FollowPlayer
	};

	States CurrentState;
	Texture EnemyTexture;
	Sprite EnemySprite;
	Vector2f Position;
	Vector2f Velocity;
	float Speed;
	float Orientation;
	Vector2f Target;
	float Range;
	int Start;
	int End;

	vector<Node*> Path;

public:
	Enemy();
	Enemy(string Tag, Texture & LoadedTexture, float x, float y);
	~Enemy();
	void Render(RenderSystem *);
	void Update(unsigned int,Graph<pair<string, int>, int>*, vector<Vector2f> *, Vector2f );
	void Movement();
	void Seek();
	Vector2f getPosition() { return Position; };
	Sprite getSprite() { return EnemySprite; };
	string getType() { return Type; };
	bool CheckBounds();
};