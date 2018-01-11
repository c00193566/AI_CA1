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
	PlayerObj->Init("Player", Vector2f(640, 360));

	UP = false;
	DOWN = false;
	RIGHT = false;
	LEFT = false;

	IsRunning = true;

	int temp[17][33] = {
		{ 5, 3, 3, 3, 3, 3, 3, 8, 0, 0, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 8, 0, 0, 5, 3, 3, 3, 3, 3, 3, 8 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 6, 3, 3, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 3, 3, 7, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 5, 3, 3, 3, 3, 3, 3, 3, 8, 1, 5, 3, 3, 3, 3, 3, 3, 3, 8, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 2, 1, 4, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 2, 1, 4, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 5, 7, 1, 6, 8, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 2, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 4 },
		{ 6, 3, 3, 3, 3, 3, 3, 7, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 6, 3, 3, 3, 3, 3, 3, 7 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 3, 3, 3, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			Level[i][j] = temp[i][j];
		}
	}
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
				Nodes.at(i)->Update(Objects.at(j)->getPosition());
			}
		}
	}

	// Update GameObjects
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(DT);

		Collision::PlayerCollision(Objects.at(i), PlayerObj);

		if (Objects.at(i)->getType() == "Wall")
		{
			for (int j = 0; j < Bullets.size(); j++)
			{
				Collision::BulletWallCollision(Objects.at(i), Bullets.at(j));
			}
		}
		else if (Objects.at(i)->getType() == "Worker")
		{
			Worker * WorkerObj = static_cast<Worker*>(Objects.at(i));
			WorkerObj->FindTarget(Nodes);
			if (!WorkerObj->getAlive())
			{
				Objects.erase(Objects.begin() + i);
				break;
			}
		}
		else if (Objects.at(i)->getType() == "AlienNest")
		{
			AlienNest * AlienObj = static_cast<AlienNest*>(Objects.at(i));
			AlienObj->FindPlayer(PlayerObj->getPosition());
			AlienObj->UpdateMissile(DT, PlayerObj->getPosition(), PlayerObj->getVelocity());
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
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 41; j++)
		{
			Sprite Tile;
			Texture TileTexture;
			bool Culled = false;

			if (!Culled)
			{
				if (Level[i][j] == 1) //Walkway
				{
					TileTexture = TextureHandler->getTexture("Walkway");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 2) //Left Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_Left");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 3) //Bottom Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_Bottom");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 4) //Right Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_Right");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 5) //Top Left Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_TopLeft");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 6) //Bottom Left Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_BottomLeft");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 7) //Bottom Right Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_BottomRight");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}

				if (Level[i][j] == 8) //Top Right Wall
				{
					TileTexture = TextureHandler->getTexture("Wall_TopRight");
					Tile.setTexture(TileTexture);
					Tile.setPosition(j * 96, i * 96);
					Renderer->RenderSprite(Tile);
				}
			}
		}
	}

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