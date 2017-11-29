#pragma once
#include "stdafx.h"
#include "RenderSystem.h"
#include "SceneManager.h"
#include "TextureLoader.h"
#include "LevelLoader.h"

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
	RenderSystem * Renderer;

	// Game stuff
	LevelLoader LoadData;
	SceneManager SceneHandler;
	TextureLoader * TextureHandler;

public:
	Game();
	~Game();
	bool Init(int, int, string);
	void Loop();
	void Update();
	void Render();
	void EventHandler();
};