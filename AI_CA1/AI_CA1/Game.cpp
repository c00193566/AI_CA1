#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init(int x, int y, string title)
{
	Renderer = new RenderWindow(VideoMode(x, y), title);

	if (Renderer == nullptr)
	{
		return false;
	}

	CurrentTime = Time::Zero;
	UpdateClock.restart();

	IsRunning = true;

	return true;
}

void Game::Loop()
{
	while (IsRunning)
	{
		EventHandler();

		CurrentTime += UpdateClock.restart();

		if (CurrentTime > FPS)
		{

			Update();
			Render();

			CurrentTime = Time::Zero;
		}
	}
}

void Game::Update()
{

}

void Game::Render()
{
	Renderer->clear(Color::White);

	// Place draw methods here

	Renderer->display();
}

void Game::EventHandler()
{
	Event event;

	while (Renderer->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			IsRunning = false;
		}
	}
}