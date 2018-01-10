#include "Missile.h"

Missile::Missile(Vector2f StartPosition)
{
	TextureLoader * TextureHandler;

	TextureHandler = TextureLoader::Instance();

	MissileTexture = TextureHandler->getTexture("Missile");

	MissileSprite.setTexture(MissileTexture);

	MissileSprite.setOrigin(2.0f, 8.0f);

	Position = StartPosition;

	MissileSprite.setPosition(Position);

	TimeAlive = 0.0f;

	MaxSpeed = 1.0f;

	Alive = true;
}

void Missile::Update(unsigned int DT, Vector2f TargetPosition, Vector2f TargetVelocity)
{
	Pursuit(TargetPosition, TargetVelocity);
	Movement();
	TimeUpdate(DT);
}

void Missile::Render(RenderSystem* Renderer)
{
	Renderer->RenderSprite(MissileSprite);
}

void Missile::Pursuit(Vector2f TargetPosition, Vector2f TargetVelocity)
{
	float TimePerdiction = 0.0f;
	float MaxTimePerdiction = 5.0f;

	Vector2f Dir = TargetPosition - Position;
	float Distance = Vector::Length(Dir);

	float Speed = Vector::Length(Velocity);

	if (Speed <= Distance / MaxTimePerdiction)
	{
		TimePerdiction = MaxTimePerdiction;
	}
	else
	{
		TimePerdiction = Distance / Speed;
	}

	Vector2f TargetPrediction = TargetPosition + TargetVelocity * TimePerdiction;

	Seek(TargetPrediction);
}

void Missile::Seek(Vector2f Target)
{
	Velocity = Target - Position;

	Velocity = Vector::Normalise(Velocity);

	Velocity *= MaxSpeed;

	Orientation = Vector::GetOrientation(Orientation, Velocity);

	MissileSprite.setRotation(Orientation);
}

void Missile::Movement()
{
	Position += Velocity;
	MissileSprite.setPosition(Position);
}

void Missile::TimeUpdate(unsigned int DT)
{
	TimeAlive += DT / 600.0f;

	if (TimeAlive >= TimeToDie)
	{
		Alive = false;
	}
}