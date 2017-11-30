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

	UP = false;
	DOWN = false;
	RIGHT = false;
	LEFT = false;

	IsRunning = true;
}

void TestScene::Initialise()
{
	for (int i = 0; i < GameData::m_maxGameObjects; i++)
	{
		if (GameData::m_gameObjectVector.at(i).type == "Walkway" || GameData::m_gameObjectVector.at(i).type == "Wall")
		{
			Objects.push_back(new Basic(GameData::m_gameObjectVector.at(i).type, TextureHandler->getTexture(GameData::m_gameObjectVector.at(i).texture),
				GameData::m_gameObjectVector.at(i).X, GameData::m_gameObjectVector.at(i).Y));
			if (GameData::m_gameObjectVector.at(i).type == "Walkway")
			{
				Nodes.push_back(new Node(Vector2f(GameData::m_gameObjectVector.at(i).X, GameData::m_gameObjectVector.at(i).Y)));
			}
		}
	}

	// Add in Worker
	Objects.push_back(new Worker("Worker", TextureHandler->getTexture("Worker"), 640, 296));
	Objects.push_back(new Worker("Worker", TextureHandler->getTexture("Worker"), 608, 104));
	Objects.push_back(new AlienNest("AlienNest", TextureHandler->getTexture("AlienNest"), 640, 104));
}

void TestScene::Update(unsigned int DT)
{
	// Camera Update
	SceneCamera.Update(PlayerObj->getPosition());

	// Player Updates
	PlayerObj->Update(DT);
	PlayerMovement();

	//Update Nodes
	for (int i = 0; i < Nodes.size(); i++)
	{
		for (int j = 0; j < Objects.size(); j++)
		{
			if (!(Objects.at(j)->getType() == "Walkway" || Objects.at(j)->getType() == "Wall"))
			{
				cout << Objects.at(j)->getType() << endl << endl;
				Nodes.at(i)->Update(Objects.at(j)->getPosition());
			}
		}
	}

	// Update GameObjects
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(DT);

		if (Objects.at(i)->getType() == "Wall")
		{
			Collision::WallCollision(Objects.at(i), PlayerObj);

			for (int j = 0; j < Bullets.size(); j++)
			{
				Collision::BulletWallCollision(Objects.at(i), Bullets.at(j));
			}
		}
		else if (Objects.at(i)->getType() == "Worker")
		{
			Worker * WorkerObj = static_cast<Worker*>(Objects.at(i));
			WorkerObj->FindTarget(Nodes);
		}
	}

	// Update bullets
	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullets.at(i)->Update(DT);

		if (!Bullets.at(i)->getAlive())
		{
			Bullets.erase(Bullets.begin() + i);
			CurrentBullets--;
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

	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullets.at(i)->Render(Renderer);
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
			Bullets.push_back(new Bullet("Bullet", TextureHandler->getTexture("Bullet"), PlayerObj->getPosition(), PlayerObj->getOrientation()));
			CurrentBullets++;
		}
		break;
	default:
		break;
	}
}