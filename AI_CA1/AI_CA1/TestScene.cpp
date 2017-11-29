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
	InputHandler.AddListener(EventListener::Event::SHOOT, this);

	// TextHandler
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

			for (int j = 0; j < Bullets.size(); j++)
			{
				Bullets.at(j)->Collision(Objects.at(i));
			}
		}
		else if (Objects.at(i)->getType() == "Bullet")
		{
			Bullet * BulletObj = static_cast<Bullet*>(Objects.at(i));

			if (!BulletObj->getAlive())
			{
				Objects.erase(Objects.begin() + i);
				RemoveBullet();
				CurrentBullets--;
				break;
			}
		}
	}
}

void TestScene::RemoveBullet()
{
	for (int i = 0; i < Bullets.size(); i++)
	{
		if (!Bullets.at(i)->getAlive())
		{
			Bullets.erase(Bullets.begin() + i);
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
	case EventListener::Event::SHOOT:
		if (CurrentBullets < MaxBullets)
		{
			Objects.push_back(new Bullet("Bullet", TextureHandler->getTexture("Bullet"), PlayerObj->getPosition(), PlayerObj->getOrientation()));
			Bullets.push_back(static_cast<Bullet*>(Objects.at(Objects.size() - 1)));
			CurrentBullets++;
		}
		break;
	default:
		break;
	}
}