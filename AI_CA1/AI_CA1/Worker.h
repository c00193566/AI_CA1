#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Path.h"

/**
* \class Worker
*
* \brief Worker object is AI that wanders around the map.
*
* This class is used to create a Worker Object. The Worker object
* just wanders around the map and will avoid collision with the enemy
* and other worker objects.
*
* \author $Author: Jack Keogh $
*/

class Worker : public GameObject
{
	/// Allows the Worker to switch between different behaviours
	enum class States
	{
		Setup,
		Search,
		FollowPath
	};

	States CurrentState; ///< State to determine what the Worker is doing.
	Texture WorkerTexture; ///< Texture for the Worker object.
	Sprite WorkerSprite; ///< Sprite for the Worker object.
	Vector2f Position; ///< Vector2f for the position of the Worker object.
	Vector2f Velocity; ///< Vector2f for the velocity of the Worker object.
	float Speed; ///< float for the speed of the Worker object.
	float Orientation; ///< float for the orientation of the Worker object. 
	float Rotation; ///< float for the rotation of the worker object.
	Vector2f Target; ///< Vector2f the target position for the Worker object.
	int Start; ///< int the start point of the path for the Worker object.
	int End; ///< int the end point of the path for the Worker object.
	bool Alive; ///< bool to determine if the Worker object is alive or not. 
	vector<Node*> Path; ///< vector of Node pointers for the path of the Worker object.

public:
	/// Creates a Worker object.
	Worker();

	/// Creates a Worker object withe initial parameters passed in.
	Worker(string Tag, Texture & LoadedTexture, float x, float y);

	/// Destroys Worker object.
	~Worker(); 

	/// This method uses the RenderSystem to draw the Worker's sprite.
	void Render(RenderSystem *);

	/**
	* \brief Updates the Worker object.
	* \param DT unsigned integer for Delta Time.
	* \param GraphData stores the node and arc data of the map.
	* \param Waypoints a vector of Vector2f variables of all the points on the map.
	*
	* Calls the necessary functions of the Worker in order to update the object. It Will
	* also carry out the path finding methods for the Worker.
	*/
	void Update(unsigned int DT, Graph<pair<string, int>, int>* GraphData, vector<Vector2f>* Waypoints);

	/// This method applies the velocity to the position and updates the sprite with the position.
	void Movement();

	/// Return Position a Vector2f variable indicating the position of the Worker object.
	Vector2f getPosition() { return Position; };

	/// Return WorkerSprite a sprite variable of the Worker object.
	Sprite getSprite() { return WorkerSprite; };

	/// Return Type a string variable indicating the type of the object.
	string getType() { return Type; };

	/// Checks if the Object is within the bounds of the target.
	bool CheckBounds();

	/// Seeks the Target
	void Seek();

	/// This method takes in a bool parameter and sets it to the Alive variable.
	void setAlive(bool set) { Alive = set; };

	/// Return Alive a boolean variable indicating if the Worker object is alive or not.
	bool getAlive() { return Alive; };

	/// This method calculates the velocity direction based on the orientation.
	void OrientationToVelocity();

	/// These methods allow the Worker object to avoid the specified type.
	void Repulsion(vector<Worker*>);
	void Repulsion(vector<Enemy*>);
};