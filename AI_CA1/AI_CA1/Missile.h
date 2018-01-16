#pragma once
#include "GameObject.h"
#include "TextureLoader.h"

/**
* \class Missile
*
* \brief Missile object to fire from AlienNest
*
* This class is used to create a Missile object at
* an object's position. The Missile follows its 
* given target.
*
* \author $Author: Jack Keogh $
*/

class Missile
{
private:
	Texture MissileTexture; ///< Texture for the Missile object.
	Sprite MissileSprite; ///< Sprite for the Missile object.
	Vector2f Position; ///< Vector2f position of the Missile object.
	Vector2f Velocity; ///< Vector2f velocity of the Missile object.
	float MaxSpeed; ///< float the max speed of the Missile object.
	float Orientation; ///< float the orientation of the Missile object.
	float TimeAlive; ///< float the time that the Missile object has been alive.
	const float TimeToDie = 5.0f; ///< const float the time the Missile object has to live.
	bool Alive; ///< bool determines if the Missile object is alive or not.

public:

	/// Creates a Missile object.
	Missile() {};

	/// Creates a Missile object with initial values passed in.
	Missile(Vector2f StartPosition);

	/// Destorys the Missile object.
	~Missile() {};

	/**
	 * \brief Updates the Missile object.
	 * \param DT unsigned integer of Delta Time.
	 * \param TargetPos Vector2f the Missile's target position.
	 * \param TargetVel Vector2f the Missile's target velocity.
	 *
	 * This method calls Pursuit, Movement and TimeUpdate passing in
	 * the relative parameters for each.
	 */
	void Update(unsigned int DT, Vector2f TargetPos, Vector2f TargetVel);

	/// This method uses the RenderSystem to render the Missile sprite.
	void Render(RenderSystem*);

	/// This method predicts where its target will be.
	void Pursuit(Vector2f TargetPos, Vector2f TargetVel);

	/// This method determines the direction of the target and applies speed in that direction.
	void Seek(Vector2f);

	/// This method updates position with velocity and applies it to the sprite.
	void Movement();

	/// This method updates TimeAlive until it reaches TimeToDie and sets alive to false.
	void TimeUpdate(unsigned int DT);

	/// Return Position a Vector2f variable of the Missile's position.
	Vector2f getPosition() { return Position; };

	/// Return MissileSprite a Sprite variable for the Missile's sprite.
	Sprite getSprite() { return MissileSprite; };

	/// Return Alive a boolean variable determining if the Missile is alive or not.
	bool getAlive() { return Alive; };

	/// This method takes in a boolean param and sets it to Alive.
	void setAlive(bool set) { Alive = set; };
};