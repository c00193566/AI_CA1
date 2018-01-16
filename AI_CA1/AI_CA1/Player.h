#pragma once
#include "GameObject.h"
#include "TextureLoader.h"

/**
* \class Player
*
* \brief Player object controllable by the user
*
* This class is used to create a Player object. It
* is controlled by the user of the game. It keeps track
* of the amount of workers collected and the number of
* lives the Player has.
*
* \author $Author: Jack Keogh $
* \author $Author: Jason Hannon$
*/

class Player : public GameObject
{
private:
	Texture PlayerTexture; ///< Texture of the Player object.
	Sprite PlayerSprite; ///< Sprite of the Player object.
	Vector2f Position; ///< Vector2f the position of the Player object.
	Vector2f Velocity; ///< Vector2f the velocity of the Player object.
	float Speed; ///< float the speed of the Player object.
	float Orientation; ///< float the rotation of the Player object.

	float MaxSpeed = 2.5f; ///< float the max speed the Player object can reach.
	float MinSpeed = 0.0f; ///< float the min speed the Player object can reach.
	int Lives = 3; ///< int the number of lives the Player object has.
	int WorkersCollected = 0; ///< int the number of workers collected by the Player object.
	int MaxWorkers; ///< int the max amount of numbers collectable.

	TextureLoader * TextureHandler; ///< TextureLoader allows access to loaded textures.

	Texture HeartTexture; ///< Texture for Heatlh.
	vector<Sprite> Hearts; ///< vector of Sprite to hold the Sprites for the Hearts.
	vector<Vector2f> Differences; ///< vector of Vector2f to place the position of hearts relative to Player.
	Vector2f HeartPosition; ///< Vector2f the initial position of the hearts.

	Font Font; ///< Font the font the text will use.
	Text WorkerText; ///< Text this will display the worker count.
	Vector2f TextPosition; ///< Vector2f the position of the text.
	Vector2f TextDifference; ///< Vector2f the difference between the Player position and Text position.

public:

	/// Creates a Player object.
	Player();

	/// Destroys a Player object.
	~Player();

	/// Initialis the Player object with set parameters.
	bool Init(string Tag, Vector2f position);

	/// Initialis the Player object with set parameters.
	bool Init(string Tag, Texture & LoadedTexture, float x, float y);

	/// This method uses the RenderSystem to draw the Player sprite.
	void Render(RenderSystem *);

	/// This method calls other functions that will update the player.
	void Update(unsigned int);

	/// This method applies velocity to position and sets the sprite's position.
	void Movement();

	/// This method carries out functions based on the string input.
	void Input(string);

	/// This method sets the base velocity depending on the orientation of the Player object.
	void SetVelocity();

	/// This method carries out the relative collision functions based on the string parameter.
	void Collision(string ObjType);

	/// Return Position a Vector2f variable indicating the position of the Player object.
	Vector2f getPosition() { return Position; };

	/// Return PlayerSprite a sprite variable.
	Sprite getSprite() { return PlayerSprite; };

	/// Return Type a string variable indicating object type.
	string getType() { return Type; };

	/// Return Velocity a Vector2f variable indicating the velocity of the Player object.
	Vector2f getVelocity() { return Velocity; };

	/// Return Orientation a float variable indicating the rotation of the Player object.
	float getOrientation() { return Orientation; };
};