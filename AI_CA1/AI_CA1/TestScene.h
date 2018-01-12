#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "InputManager.h"
#include "Graph.h"
#include "TextureLoader.h"
#include "GameData.h"
#include "Player.h"
#include "Camera.h"
#include "Basic.h"
#include "Bullet.h"
#include "Worker.h"
#include "Collision.h"
#include "AlienNest.h"
#include "Enemy.h"

typedef GraphArc<string, int> Arc;
typedef GraphNode<pair<string, int>, int> Node;

class TestScene : public Scene, public EventListener
{
private:
	// Systems
	InputManager InputHandler;
	Camera SceneCamera;
	TextureLoader * TextureHandler;

	// GameObjects
	Player* PlayerObj;
	vector<Basic*> Map;
	vector<Worker*> Workers;
	vector<Enemy*> Enemies;
	vector<AlienNest*> Nests;
	vector<Bullet*> Bullets;
	int MaxBullets = 10;
	int CurrentBullets = 0;

	// Map Data
	Graph<pair<string, int>, int> * GraphData;
	vector<Vector2f> Waypoints;

	//Bools to keep track of button presses
	bool UP;
	bool DOWN;
	bool LEFT;
	bool RIGHT;

	// Private methods
	void PlayerMovement();

public:
	TestScene();
	~TestScene() {};
	void Initialise();
	void LoadGraph();
	void Update(unsigned int);
	void Render(RenderSystem * Renderer);
	void Event(RenderSystem * Renderer);
	void onEvent(EventListener::Event);
	bool Running() { return IsRunning; };
};