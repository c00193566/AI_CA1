#include "Game.h"

Game::Game()
{
	TextureHandler = TextureLoader::Instance();

	TextureHandler->addTexture("Player", "Assets/Player.png");
	TextureHandler->addTexture("Walkway_01", "Assets/Walkway_01.png");
	TextureHandler->addTexture("Wall_TopLeft", "Assets/Wall_TopLeft.png");
	TextureHandler->addTexture("Wall_BottomRight", "Assets/Wall_BottomRight.png");
	TextureHandler->addTexture("Wall_BottomLeft", "Assets/Wall_BottomLeft.png");
	TextureHandler->addTexture("Wall_TopRight", "Assets/Wall_TopRight.png");
	TextureHandler->addTexture("Wall_Left", "Assets/Wall_Left.png");
	TextureHandler->addTexture("Wall_Right", "Assets/Wall_Right.png");
	TextureHandler->addTexture("Wall_Bottom", "Assets/Wall_Bottom.png");
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