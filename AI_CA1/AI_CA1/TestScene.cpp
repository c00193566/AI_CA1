#include "TestScene.h"

TestScene::TestScene()
{
	InputHandler.AddListener(EventListener::Event::QUIT, this);
	InputHandler.AddListener(EventListener::Event::UP, this);
	InputHandler.AddListener(EventListener::Event::DOWN, this);
	InputHandler.AddListener(EventListener::Event::LEFT, this);
	InputHandler.AddListener(EventListener::Event::RIGHT, this);
	InputHandler.AddListener(EventListener::Event::UPR, this);
	InputHandler.AddListener(EventListener::Event::DOWNR, this);
	InputHandler.AddListener(EventListener::Event::LEFTR, this);
	InputHandler.AddListener(EventListener::Event::RIGHTR, this);

	PlayerObj = new Player;
	PlayerObj->Init("Player", "Assets/Player.png", Vector2f(640, 360));

	// First Room
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 640, 264));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 640, 360));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 640, 328));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 640, 296));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 608, 360));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 608, 328));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 608, 296));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 672, 360));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 672, 328));
	Objects.push_back(new Basic("Walkway", "Assets/Walkway_01.png", 672, 296));

	// Walls
	Objects.push_back(new Basic("Wall", "Assets/Wall_TopLeft.png", 576, 264));
	Objects.push_back(new Basic("Wall", "Assets/Wall_BottomRight.png", 608, 264));
	Objects.push_back(new Basic("Wall", "Assets/Wall_BottomLeft.png", 672, 264));
	Objects.push_back(new Basic("Wall", "Assets/Wall_TopRight.png", 704, 264));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Left.png", 576, 296));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Left.png", 576, 328));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Left.png", 576, 360));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Right.png", 704, 296));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Right.png", 704, 328));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Right.png", 704, 360));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Bottom.png", 608, 392));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Bottom.png", 640, 392));
	Objects.push_back(new Basic("Wall", "Assets/Wall_Bottom.png", 672, 392));
	Objects.push_back(new Basic("Wall", "Assets/Wall_BottomLeft.png", 576, 392));
	Objects.push_back(new Basic("Wall", "Assets/Wall_BottomRight.png", 704, 392));



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