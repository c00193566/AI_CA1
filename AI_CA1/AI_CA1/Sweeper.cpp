#include "Sweeper.h"

Sweeper::Sweeper()
{

}

Sweeper::Sweeper(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	SweeperTexture = LoadedTexture;

	SweeperSprite.setTexture(SweeperTexture);

	SweeperSprite.setOrigin(SweeperTexture.getSize().x / 2, SweeperTexture.getSize().y / 2);

	Position = Vector2f(x, y);
	SweeperSprite.setPosition(Position);

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 1.0f;

	CurrentState = States::Setup;
	Alive = true;
	Start = -1000;
	End = -1000;

	Rotation = 0;

	Path = vector<Node*>();
}

Sweeper::~Sweeper()
{

}

void Sweeper::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(SweeperSprite);
}

void Sweeper::Update(unsigned int DT, Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * Waypoints)
{

	Movement();
}

void Sweeper::Movement()
{
	Velocity *= Speed;
	Position += Velocity;
	SweeperSprite.setPosition(Position);
}