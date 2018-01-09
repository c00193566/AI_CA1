#include "Missile.h"

Missile::Missile(Vector2f StartPosition)
{
	TextureLoader * TextureHandler;

	TextureHandler = TextureLoader::Instance();

	MissileTexture = TextureHandler->getTexture("Missile");

	MissileSprite.setTexture(MissileTexture);

	MissileSprite.setOrigin(8.0f, 2.0f);

	Position = StartPosition;

	MissileSprite.setPosition(Position);

	TimeAlive = 0.0f;

	Speed = 5.0f;

	Alive = true;
}

void Missile::Update(unsigned int DT, Vector2f Target)
{
	Pursuit(Target);
	TimeUpdate(DT);
}

void Missile::Render(RenderSystem* Renderer)
{
	Renderer->RenderSprite(MissileSprite);
}

void Missile::Pursuit(Vector2f Target)
{

}

void Missile::TimeUpdate(unsigned int DT)
{
	TimeAlive += DT / 600.0f;

	cout << TimeAlive << endl;

	if (TimeAlive >= TimeToDie)
	{
		Alive = false;
	}
}