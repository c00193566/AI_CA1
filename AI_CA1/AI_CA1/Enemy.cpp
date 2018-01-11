#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	WorkerTexture = LoadedTexture;

	WorkerSprite.setTexture(WorkerTexture);

	WorkerSprite.setOrigin(8.0f, 8.0f);

	Position = Vector2f(x, y);
	WorkerSprite.setPosition(Position);

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 1.0f;

	Range = 160;

	Wander = false;

	Culling = false;
}

Enemy::~Enemy()
{

}

void Enemy::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(WorkerSprite);
}

void Enemy::Update(unsigned int DT)
{

}

void Enemy::Movement()
{
		
}
