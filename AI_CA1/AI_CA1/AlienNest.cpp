#include "AlienNest.h"

AlienNest::AlienNest()
{

}

AlienNest::AlienNest(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	AlienNestTexture = LoadedTexture;

	AlienNestSprite.setTexture(AlienNestTexture);

	AlienNestSprite.setOrigin(8.0f, 8.0f);

	Position = Vector2f(x, y);

	AlienNestSprite.setPosition(Position);

	PlayerFound = false;

	TimeDelay = 3.0f;

	Range = 128;

	MissileExists = false;
}

AlienNest::~AlienNest()
{

}

void AlienNest::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(AlienNestSprite);

	for (int i = 0; i < Missiles.size(); i++)
	{
		Missiles.at(i)->Render(Renderer);
	}
}

void AlienNest::Update(unsigned int DT)
{
}

void AlienNest::UpdateMissile(unsigned int DT, Vector2f TargetPosition, Vector2f TargetVelocity)
{
	for (int i = 0; i < Missiles.size(); i++)
	{
		Missiles.at(i)->Update(DT, TargetPosition, TargetVelocity);
	}

	UpdateMissileInfo();
}

void AlienNest::UpdateMissileInfo()
{
	for (int i = 0; i < Missiles.size(); i++)
	{
		if (!Missiles.at(i)->getAlive())
		{
			MissileExists = false;
			PlayerFound = false;
			Missiles.clear();
			TimeDelay = 0.0f;
			break;
		}
	}
}

void AlienNest::FindPlayer(Vector2f PlayerPosition)
{
	if (!PlayerFound)
	{
		TimeDelay += 1.0f / 60.0f;

		cout << TimeDelay << endl;

		if (TimeDelay > 2.0f)
		{
			Vector2f Difference = Position - PlayerPosition;
			float Distance = Vector::Length(Difference);

			if (Distance <= Range)
			{
				PlayerFound = true;
				FireMissile(PlayerPosition);
			}
		}
	}
}

void AlienNest::FireMissile(Vector2f PlayerPosition)
{
	if (PlayerFound && !MissileExists)
	{
		Missiles.push_back(new Missile(Position));
		MissileExists = true;
	}
}
