#pragma once
#include "stdafx.h"
#include "GameObject.h"

/**
* \class Bullet
*
* \brief Bullet object to fire from player
*
* This class is used to create a bullet object at 
* an object's position. The bullet fires in the direction
* the object is facing at a set speed. It stays alive
* for a set amount of time.
*
* \author $Author: Jack Keogh $
*/

class Bullet : public GameObject
{
private:
	Texture BulletTexture; ///< Texture for Bullet object.
	Sprite BulletSprite; ///< Sprite for Bullet object.
	Vector2f Position; ///< Vector2f for Bullet object Position.
	Vector2f Velocity; ///< Vector2f for Bullet Object Velocity.
	float Speed; ///< float for Bullet object Speed.
	float TimeAlive; ///< float for Bullet object Time Alive.

	bool Alive; ///< bool for Bullet object Alive.

public:
	/// Creates a Bullet object.
	Bullet();

	/// Creates a Bullet object with initial values passed in.
	Bullet(string Tag, Texture & LoadedTexture, Vector2f InputPosition, float Direction);

	/// Destroys a Bullet object.
	~Bullet();

	/// This method uses the RenderSystem to draw the BulletSprite
	void Render(RenderSystem * Renderer);

	/**
	 * \brief Updates the bullet
	 * \param DT an unsigned integer used for delta time.
	 * 
	 * Update uses DT to update TimeAlive. When TimeAlive
	 * reaches 1.0f Dead() is called.
	 */
	void Update(unsigned int DT);

	/// This method sets Alive to false
	void Dead();

	/// Return BulletSprite the sprite component of the object.
	Sprite getSprite() { return BulletSprite; };

	/// Return Type a string variable that dictates the object type.
	string getType() { return Type; };

	/// Return Position a Vector2f variable that gives the object a position.
	Vector2f getPosition() { return Position; };

	/// Return Alive a bool variable that determines if the object is alive or not.
	bool getAlive() { return Alive; };
};