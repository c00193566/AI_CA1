#include "Basic.h"

Basic::Basic(string Tag, string Path, float x, float y)
{
	Type = Tag;

	if (!(BasicTexture.loadFromFile(Path)))
	{
		cout << "Could not load texture for player" << endl;
	}

	BasicSprite.setTexture(BasicTexture);

	BasicSprite.setOrigin(16.0f, 16.0f);

	Position = Vector2f(x, y);
	BasicSprite.setPosition(Position);
}

Basic::~Basic()
{

}

void Basic::Update(unsigned int DT)
{

}

void Basic::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(BasicSprite);
}