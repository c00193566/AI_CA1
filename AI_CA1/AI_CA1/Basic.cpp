#include "Basic.h"

Basic::Basic(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	BasicTexture = LoadedTexture;

	BasicSprite.setTexture(BasicTexture);

	BasicSprite.setOrigin(16.0f, 16.0f);

	Position = Vector2f(x, y);
	BasicSprite.setPosition(Position);
}

Basic::~Basic()
{

}

void Basic::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(BasicSprite);
}