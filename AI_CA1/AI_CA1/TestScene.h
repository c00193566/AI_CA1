#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "InputManager.h"
#include "TextureLoader.h"
#include "GameData.h"
#include "Node.h"
#include "Player.h"
#include "Camera.h"
#include "Basic.h"
#include "Bullet.h"
#include "Worker.h"
#include "Collision.h"
#include "AlienNest.h"
#include "Enemy.h"

class TestScene : public Scene, public EventListener
{
private:
	// Systems
	InputManager InputHandler;
	Camera SceneCamera;
	TextureLoader * TextureHandler;

	// GameObjects
	Player* PlayerObj;
	vector<GameObject*> Objects;
	vector<Node*> Nodes;
	vector<Bullet*> Bullets;
	int MaxBullets = 10;
	int CurrentBullets = 0;

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
	void Update(unsigned int);
	void Render(RenderSystem * Renderer);
	void Event(RenderSystem * Renderer);
	void onEvent(EventListener::Event);
	bool Running() { return IsRunning; };
};