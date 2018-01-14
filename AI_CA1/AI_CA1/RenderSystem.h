#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class RenderSystem
{
private:
	RenderWindow Renderer;

public:
	RenderSystem(int, int, string);
	~RenderSystem();

	//Render Sprite
	void RenderSprite(Sprite &);

	//Render Text
	void RenderText(Text &);

	RenderWindow & getRenderer() { return Renderer; }
	void setView(View & Camera);
};