#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Path.h"

/**
* \class Enemy
*
* \brief Enemy object wanders and seeks player when in range.
*
* This class wanders around the world searching for the player.
* When the player is in range the Enemy will plan the closest route
* to the player, when it is near the player it will begin to follow
* and fire projectiles at the player.
*
* \author $Author: Jack Keogh $
* \author $Author: Jason Hannon $
*/

class Enemy : public GameObject
{
	/// Allows the Enemy to switch between different behaviours
	enum class States
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
	Vector2f Target; ///< Vecotr2f the Enemy's target position.
	float MaxRange; ///< float for the max range of the Enemy.
	float MinRange; ///< float for the minimum range of the Enemy.
	int Start; ///< int for the start point of the path.
	int End; ///< int for the end point of the path.

	vector<Node*> Path; ///< vector storage of Node pointer for the Enemy's path.

public:
	/// Creates an Enemy object.
	Enemy();

	/// Creates an Enemy object with initial values passed.
	Enemy(string Tag, Texture & LoadedTexture, float x, float y);

	/// Destroys an Enemy object.
	~Enemy();

	/// This method uses the RenderSystem to draw the Enemy Sprite.
	void Render(RenderSystem *);

	/**
	 * \brief Updates the Enemy object.
	 * \param DT unsigned integer for Delta Time.
	 * \param GraphData stores the node and arc data of the map.
	 * \param Waypoints a vector of Vector2f variables of all the points on the map.
	 * \param PlayerPos a Vector2f that indicates the Player objects position.
	 *
	 * Updates the Enemy object based on its current state. It keeps track of the player
	 * position to determine the distance between it and if it is in range or not. Carrys
	 * out a wander, search and follow function.
	 */
	void Update(unsigned int DT,Graph<pair<string, int>, int>* GraphData, vector<Vector2f> * Waypoints, Vector2f PlayerPos);

	/// This method adds the velocity to the Position and applies it to the Sprite
	void Movement();

	/// This method determines velocity direction, applies speed to it and updates the Sprites rotation.
	void Seek();

	/// Return Position a Vector2f variable that gives the object a position.
	Vector2f getPosition() { return Position; };

	/// Return EnemySprite the sprite component of the object.
	Sprite getSprite() { return EnemySprite; };

	/// Return Type a string variable that dictates the object type.
	string getType() { return Type; };

	/// Checks if the object is within bounds of its target.
	bool CheckBounds();
};