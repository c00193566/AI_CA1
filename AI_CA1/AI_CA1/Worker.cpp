#include "Worker.h"

Worker::Worker()
{

}

Worker::Worker(string Tag, Texture & LoadedTexture, float x, float y)
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

	TargetFound = false;
	TargetReached = false;
}

Worker::~Worker()
{

}

void Worker::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(WorkerSprite);
}

void Worker::Update(unsigned int DT)
{
	if (TargetFound)
	{
		Movement();
	}

	if (Position == Target)
	{
		TargetFound = false;
	}
}

void Worker::Movement()
{
		Velocity = Target - Position;

		Velocity = Vector::Normalise(Velocity);

		Velocity *= Speed;

		Orientation = Vector::GetOrientation(Orientation, Velocity);

		WorkerSprite.setRotation(Orientation);

		Position += Velocity;
		WorkerSprite.setPosition(Position);
}