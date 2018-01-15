#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Missile.h"

/**
 * \class AlienNest
 *
 * \brief Alien Nest object to fire missile at player
 *
 * This class is meant to fire a missile at the player
 * object. Once the player object comes into range of 
 * the Alien Nest and a delay timer reaches 2 seconds
 * a missile will fire if it does not already exist.
 *
 * \author $Author: Jason Hannon $
 */


class AlienNest : public GameObject
{
private:
	Texture AlienNestTexture; ///< Texture for the Alien Nest
	Sprite AlienNestSprite; ///< Sprite for the Alien Nest
	Vector2f Position; ///< Vector2f the position of the Alien Nest
	float Range; ///< float the range the AlienNest has
	bool PlayerFound; ///< bool if the player is in range
	bool MissileExists; ///< bool if a missile already exists

	vector<Missile*> Missiles; ///< vector storage for the missile
	float TimeDelay; ///< float time delay to fire next missile

public:
	/// Create an AlienNest
	AlienNest();

	/// Create an AlienNest with initial values passed in
	AlienNest(string Tag, Texture & LoadedTexture, float x, float y);

	/// Destroy AlienNest
	~AlienNest();

	/// This method uses the rendersystem to render the AlienNest Sprite and Missile
	void Render(RenderSystem *);

	/// An update function
	void Update(unsigned int);

	/**
	 * \brief A method used to update the missile.
	 * \param DT an unsigned integer used for delta time.
	 * \param TargetPosition a Vector2f used for missile update.
	 * \param TargetVelocity a Vector2f used for missile update.
	 *
	 * This method calls the update method for the missile passing 
	 * it the parameters it takes in. It also calls the UpdateMissileInfo()
	 * method.
	 */
	void UpdateMissile(unsigned int DT, Vector2f TargetPosition, Vector2f TargetVelocity);

	/// Return AlienNestSprite the sprite component of the object.
	Sprite getSprite() { return AlienNestSprite; };

	/// Return Type a string variable that dictates the object type.
	string getType() { return Type; };

	/// Return Position a Vector2f variable that gives the object a position.
	Vector2f getPosition() { return Position; };

	/**
	 * This method checks if the missile is alive or not.
	 * If it is not alive it updates the data referring
	 * to the missile and removes it from the vector.
	 */
	void UpdateMissileInfo();

	/**
	 * \brief A search function.
	 * \param PlayerPosition a Vector2f that gives the player's position.
	 *
	 * If the object has not found the player it will update the TimeDelay
	 * variable. After this variable has reached 2.0f it will carry out
	 * simple calculations that will find if the player object is in range
	 * or not. If it is in range, player found becomes true and FireMissile()
	 * is called.
	 */
	void FindPlayer(Vector2f PlayerPosition);

	/// Creates a new missile and if one does not exist
	void FireMissile();

	/// Return Missiles a vector container for Missile objects.
	vector<Missile*> getMissiles() { return Missiles; };
};
