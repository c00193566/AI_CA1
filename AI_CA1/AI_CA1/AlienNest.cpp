#include "AlienNest.h"

AlienNest::AlienNest()
{

}

AlienNest::AlienNest(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	AlienNestTexture = LoadedTexture;

	AlienNestSprite.setTexture(AlienNestTexture);

	AlienNestSprite.setOrigin(8.0f, 8.0f);

	Position = Vector2f(x, y);

	AlienNestSprite.setPosition(Position);

	PlayerFound = false;

	Range = 64;
}

AlienNest::~AlienNest()
{

}

void AlienNest::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(AlienNestSprite);
}

void AlienNest::Update(unsigned int DT)
{

}

void AlienNest::FindPlayer(Vector2f PlayerPosition)
{
	if (!PlayerFound)
	{
		Vector2f Difference = Position - PlayerPosition;
		float Distance = Vector::Length(Difference);

		if (Distance <= Range)
		{
			PlayerFound = true;
		}
	}
}
