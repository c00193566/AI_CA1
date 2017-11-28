#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init(int x, int y, string title)
{
	Renderer = new RenderSystem(x, y, title);

	CurrentTime = Time::Zero;
	UpdateClock.restart();

	IsRunning = true;

	SceneHandler = SceneManager(Renderer);

	return true;
}

void Game::Loop()
{
	while (IsRunning)
	{
		IsRunning = SceneHandler.getScene()->Running();

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
	unsigned int DeltaTime = CurrentTime.asSeconds();

	SceneHandler.UpdateScene(DeltaTime);
}

void Game::Render()
{
	Renderer->getRenderer().clear(Color::Black);

	SceneHandler.RenderScene(Renderer);

	Renderer->getRenderer().display();
}

void Game::EventHandler()
{
	SceneHandler.EventScene(Renderer);
}