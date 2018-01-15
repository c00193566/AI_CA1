#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Path.h"

/**
* \class Enemy
*
* \brief Enemy object wanders and seeks player when in range.
*
* This class is wanders around the world searching for the player.
* When the player is in range the Enemy will plan the closest route
* to the player, when it is near the player it will begin to follow
* and fire projectiles at the player.
*
* \author $Author: Jack Keogh $
* \author $Author: Jason Hannon $
*/

class Enemy : public GameObject
{
	enum class States /// Allows the Enemy to switch between different behaviours
	{
		Setup,
		Search,
		FollowPath,
		FollowPlayer
	};

	States CurrentState; ///< State to determine what the Enemy is doing.
	Texture EnemyTexture; ///< Texture for the Enemy object.
	Sprite EnemySprite; ///< Sprite for the Enemy object.
	Vector2f Position; ///< Vector2f for the position of the Enemy object.
	Vector2f Velocity; ///< Vector2f for the velocity of the Enemy object.
	float Speed; ///< float for the speed of the Enemy object.
	float Orientation; ///< float for the orientation of the enemy object.
	Vector2f Target;
	float MaxRange;
	float MinRange;
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