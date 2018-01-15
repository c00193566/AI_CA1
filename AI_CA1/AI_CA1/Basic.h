#pragma once
#include "GameObject.h"

class Basic : public GameObject
{
private:
	Texture BasicTexture; ///< Texture for the basic object.
	Sprite BasicSprite; ///< Sprite for the basic object.
	Vector2f Position; ///< Vector2f position of the basic object.

public:
	/// Creates a Basic object.
	Basic() {};

	/// Creates a Basic object with initial values passed in.
	Basic(string Tag, Texture & LoadedTexture, float x, float y);

	/// Destroys a Basic object.
	~Basic();

	/// This method uses the RenderSystem to draw the BasicSprite
	void Render(RenderSystem *);

	/// Return Sprite of the Basic object.
	Sprite getSprite() { return BasicSprite; };

	/// Return Type a string variable that dictates the object type.
	string getType() { return Type; };

	/// Return Position a Vector2f variable that gives the object a position.
	Vector2f getPosition() { return Position; };
};