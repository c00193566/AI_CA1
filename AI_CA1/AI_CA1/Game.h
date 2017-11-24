#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class Game
{
private:
	// Stuff for loop
	Time CurrentTime;
	const Time FPS = seconds(1.0f / 60.0f);
	Clock UpdateClock;
	bool IsRunning;

	// Render stuff
	RenderWindow * Renderer = nullptr;

	// Game stuff


public:
	Game();
	~Game();
	bool Init(int, int, string);
	void Loop();
	void Update();
	void Render();
	void EventHandler();

};