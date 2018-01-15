#include "TestScene.h"

TestScene::TestScene()
{
	// Load in Waypoints
	LoadGraph();

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
}

void TestScene::Initialise()
{
	for (int i = 0; i < GameData::m_maxGameObjects; i++)
	{
		if (GameData::m_gameObjectVector.at(i).type == "Walkway" || GameData::m_gameObjectVector.at(i).type == "Wall")
		{
			Map.push_back(new Basic(GameData::m_gameObjectVector.at(i).type, TextureHandler->getTexture(GameData::m_gameObjectVector.at(i).texture),
				GameData::m_gameObjectVector.at(i).X, GameData::m_gameObjectVector.at(i).Y));
		}
	}

	// Add in Worker
	Workers.push_back(new Worker("Worker", TextureHandler->getTexture("Worker"), 640, 296));
	Workers.push_back(new Worker("Worker", TextureHandler->getTexture("Worker"), 608, 104));
	Enemies.push_back(new Enemy("Enemy", TextureHandler->getTexture("Enemy"), 608, 104));
	Nests.push_back(new AlienNest("AlienNest", TextureHandler->getTexture("AlienNest"), 640, 104));
}

void TestScene::LoadGraph()
{
	GraphData = new Graph<pair<string, int>, int>(4);

	ifstream myfile;
	
	int Max = numeric_limits<int>::max() - 10000;

	myfile.open("Resources/Nodes.txt");

	string Name;
	int index = 0;
	int X = 0; 
	int Y = 0;

	while (myfile >> Name >> X >> Y)
	{
		GraphData->addNode(pair<string, int>(Name, Max), index);
		Waypoints.push_back(Vector2f(X, Y));
		index++;
	}

	myfile.close();

	//Adds arcs
	myfile.open("Resources/Arcs.txt");

	int from, to, weight;

	while (myfile >> from >> to >> weight)
	{
		GraphData->addArc(from, to, weight);
	}

	myfile.close();

}
void TestScene::Update(unsigned int DT)
{
	// Camera Update
	SceneCamera.Update(PlayerObj->getPosition());
	// Player Updates
	PlayerObj->Update(DT);
	PlayerMovement();
	// Update GameObjects
	for (int i = 0; i < Workers.size(); i++)
	{
		Workers.at(i)->Repulsion(Workers);
		Workers.at(i)->Repulsion(Enemies);
		Workers.at(i)->Update(DT, GraphData, &Waypoints);
		Collision::PlayerCollision(Workers.at(i), PlayerObj);
	}

	for (int i = 0; i < Nests.size(); i++)
	{
		Nests.at(i)->Update(DT);
		Nests.at(i)->FindPlayer(PlayerObj->getPosition());
		Nests.at(i)->UpdateMissile(DT, PlayerObj->getPosition(), PlayerObj->getVelocity());
		Collision::PlayerCollision(Nests.at(i), PlayerObj);
	}

	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies.at(i)->Update(DT, GraphData, &Waypoints, PlayerObj->getPosition());
		Collision::PlayerCollision(Enemies.at(i), PlayerObj);
	}

	// Update bullets
	if (Bullets.size() > 0)
	{
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
	for (int i = 0; i < Map.size(); i++)
	{
		Map.at(i)->Render(Renderer);
		Collision::PlayerCollision(Map.at(i), PlayerObj);
	}

	for (int i = 0; i < Workers.size(); i++)
	{
		Workers.at(i)->Render(Renderer);
		if (!Workers.at(i)->getAlive())
		{
			Workers.erase(Workers.begin() + i);
			break;
		}
	}

	for (int i = 0; i < Nests.size(); i++)
	{
		Nests.at(i)->Render(Renderer);
	}

	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies.at(i)->Render(Renderer);
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