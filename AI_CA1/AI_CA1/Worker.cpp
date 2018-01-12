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

	Culling = false;

	Alive = true;
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

void Worker::FindTarget(vector<Node*> Nodes)
{
	if (!TargetFound)
	{
		vector<Node*> PossibleTargets;

		for (int i = 0; i < Nodes.size(); i++)
		{
			Vector2f Difference = Position - Nodes.at(i)->getPosition();
			float Distance = Vector::Length(Difference);

			if (!(Distance > 32 || Distance == 0))
			{
				if (!(Nodes.at(i)->Occupied()))
				{
					PossibleTargets.push_back(Nodes.at(i));
				}
			}
		}

		if (PossibleTargets.size() != NULL)
		{
			int RandomChoice = rand() % PossibleTargets.size();

			Target = PossibleTargets.at(RandomChoice)->getPosition();

			TargetFound = true;
		}
	}
}