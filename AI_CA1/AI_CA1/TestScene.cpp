#include "TestScene.h"

TestScene::TestScene()
{
	// Set up listeners for input handler
	InputHandler.AddListener(EventListener::Event::QUIT, this);
	InputHandler.AddListener(EventListener::Event::UP, this);
	InputHandler.AddListener(EventListener::Event::DOWN, this);
	InputHandler.AddListener(EventListener::Event::LEFT, this);
	InputHandler.AddListener(EventListener::Event::RIGHT, this);
	InputHandler.AddListener(EventListener::Event::UPR, this);
	InputHandler.AddListener(EventListener::Event::DOWNR, this);
	InputHandler.AddListener(EventListener::Event::LEFTR, this);
	InputHandler.AddListener(EventListener::Event::RIGHTR, this);

	TextureHandler = TextureLoader::Instance();

	// Set Up Player
	PlayerObj = new Player;
	PlayerObj->Init("Player", TextureHandler->getTexture("Player"), Vector2f(640, 360));

	// First Room
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 640, 264));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 640, 360));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 640, 328));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 640, 296));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 608, 360));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 608, 328));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 608, 296));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 672, 360));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 672, 328));
	Objects.push_back(new Basic("Walkway", TextureHandler->getTexture("Walkway_01"), 672, 296));

	// Walls
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_TopLeft"), 576, 264));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_BottomRight"), 608, 264));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_BottomLeft"), 672, 264));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_TopRight"), 704, 264));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Left"), 576, 296));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Left"), 576, 328));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Left"), 576, 360));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Right"), 704, 296));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Right"), 704, 328));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Right"), 704, 360));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Bottom"), 608, 392));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Bottom"), 640, 392));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_Bottom"), 672, 392));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_BottomLeft"), 576, 392));
	Objects.push_back(new Basic("Wall", TextureHandler->getTexture("Wall_BottomRight"), 704, 392));

	// Add in Worker
	Objects.push_back(new Worker("Worker", TextureHandler->getTexture("Worker"), 640, 296));

	UP = false;
	DOWN = false;
	RIGHT = false;
	LEFT = false;

	IsRunning = true;
}

void TestScene::Update(unsigned int DT)
{
	// Camera Update
	SceneCamera.Update(PlayerObj->getPosition());

	// Player Updates
	PlayerObj->Update(DT);
	PlayerMovement();

	// Update GameObjects
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(DT);

		if (Objects.at(i)->getType() == "Wall")
		{
			Collision::WallCollision(Objects.at(i), PlayerObj);
		}
		else if (Objects.at(i)->getType() == "Worker")
		{
			Worker * WorkerObj = static_cast<Worker*>(Objects.at(i));
			WorkerObj->FindTarget(Objects);
		}
	}
}

void TestScene::PlayerMovement()
{
	if (UP)
	{
		PlayerObj->Input("UP");
	}
	else if (DOWN)
	{
		PlayerObj->Input("DOWN");
	}

	if (RIGHT)
	{
		PlayerObj->Input("RIGHT");
	}
	else if (LEFT)
	{
		PlayerObj->Input("LEFT");
	}
}

void TestScene::Render(RenderSystem *Renderer)
{
	// Renderer GameObjects
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Render(Renderer);
	}

	Renderer->setView(SceneCamera.getView());
	PlayerObj->Render(Renderer);
}

void TestScene::Event(RenderSystem * Renderer)
{
	InputHandler.ProcessInput(Renderer);
}

void TestScene::onEvent(EventListener::Event evt)
{
	switch (evt)
	{
	case EventListener::Event::QUIT:
		IsRunning = false;
		break;
	case EventListener::Event::UP:
		UP = true;
		break;
	case EventListener::Event::DOWN:
		DOWN = true;
		break;
	case EventListener::Event::LEFT:
		LEFT = true;
		break;
	case EventListener::Event::RIGHT:
		RIGHT = true;
		break;
	case EventListener::Event::UPR:
		UP = false;
		break;
	case EventListener::Event::DOWNR:
		DOWN = false;
		break;
	case EventListener::Event::LEFTR:
		LEFT = false;
		break;
	case EventListener::Event::RIGHTR:
		RIGHT = false;
		break;
	default:
		break;
	}
}