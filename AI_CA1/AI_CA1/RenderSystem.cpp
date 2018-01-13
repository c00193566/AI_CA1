#include "RenderSystem.h"

RenderSystem::RenderSystem(int x, int y, string title)
{
	Renderer.create(VideoMode(x, y), title);
}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::RenderSprite(Sprite & SpriteRender)
{
	Renderer.draw(SpriteRender);
}

void RenderSystem::RenderText(Text & TextRenderer)
{
	Renderer.draw(TextRenderer);
}

void RenderSystem::setView(View & Camera)
{
	Renderer.setView(Camera);
}