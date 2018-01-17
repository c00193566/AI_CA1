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

	MaxRange = 128;
	MinRange = 32;

	Rotation = 0;

	Path = vector<Node*>();

	WorkerTarget = nullptr;
}

Sweeper::~Sweeper()
{
	
}

void Sweeper::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(SweeperSprite);
}

void Sweeper::Update(unsigned int DT, Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * Waypoints, vector<Worker*> * Workers)
{
	if (CurrentState == States::Setup)
	{
		Target = Path::NearestPointPosition(Waypoints, Position);

		if (CheckBounds())
		{
			CurrentState = States::Search;
		}
	}
	else if (CurrentState == States::Search)
	{
		// Get the Closest Worker
		if (Workers->size() > 0)
		{
			int MinDistance = numeric_limits<int>::max() - 10000; // infinity
			for (int i = 0; i < Workers->size(); i++)
			{
				Vector2f Dir = Position - Workers->at(i)->getPosition();
				float Dis = Vector::Length(Dir);

				if (Dis < MinDistance)
				{
					WorkerTarget = Workers->at(i);
				}
			}
		}
		else
		{
			WorkerTarget = nullptr;
		}

		// Variables for checking distance
		Vector2f Dir = Vector2f();
		float Dis = numeric_limits<int>::max() - 10000;

		// Check if in range of WorkerTarget
		if (WorkerTarget != nullptr)
		{
			Dir = WorkerTarget->getPosition() - Position;
			Dis = Vector::Length(Dir);
		}

		if (Dis < MaxRange)
		{
			Start = Path::NearestPointIndex(Waypoints, Position);
			End = Path::NearestPointIndex(Waypoints, WorkerTarget->getPosition());
			CurrentState = States::FollowWorker;
		}
		else
		{
			// Not in Range, generate random index
			int Point = rand() % Waypoints->size();
			End = Path::NearestPointIndex(Waypoints, Position);

			// Don't want to go to last point
			if (Point != End)
			{
				Start = Path::NearestPointIndex(Waypoints, Position);
				End = Point;
				Path = Path::UniformCostSearch(GraphData, Waypoints, Start, End);
				CurrentState = States::FollowPath;
			}
		}
	}
	else if (CurrentState == States::FollowPath)
	{
		// Check if reached endpoint
		if (Start == End)
		{
			CurrentState = States::Search;
			return;
		}

		if (Path.size() > 0)
		{
			string PointName = Path.at(Path.size() - 1)->data().first;
			int PointIndex = stoi(PointName);
			Target = Waypoints->at(PointIndex);

			if (CheckBounds())
			{
				Start = Path::NearestPointIndex(Waypoints, Position);
				Path.pop_back();
			}
		}

		// Check if comes into range
		if (WorkerTarget != nullptr)
		{
			Vector2f Dir = WorkerTarget->getPosition() - Position;
			float Dis = Vector::Length(Dir);

			if (Dis < MaxRange)
			{
				CurrentState = States::Search;
			}
		}
	}
	else if (CurrentState == States::FollowWorker)
	{
		if (WorkerTarget != nullptr)
		{
			if (!WorkerTarget->getAlive())
			{
				CurrentState = States::Search;
			}

			// Check if comes into range
			Vector2f Dir = WorkerTarget->getPosition() - Position;
			float Dis = Vector::Length(Dir);

			if (Dis > MaxRange)
			{
				CurrentState = States::Search;
				return;
			}

			// Check if reached endpoint
			if (Start == End || Dis < MinRange)
			{
				Target = WorkerTarget->getPosition();
			}

			if (Dis > MinRange)
			{
				if (Path.size() > 0)
				{
					string PointName = Path.at(Path.size() - 1)->data().first;
					int PointIndex = stoi(PointName);
					Target = Waypoints->at(PointIndex);

					if (CheckBounds())
					{
						Start = Path::NearestPointIndex(Waypoints, Position);
						Path.pop_back();
					}
				}
			}
		}
		else
		{
			CurrentState = States::Search;
		}
	}

	Seek();
	Movement();
}

void Sweeper::Seek()
{
	Velocity = Target - Position;

	Velocity = Vector::Normalise(Velocity);

	Orientation = Vector::GetOrientation(Orientation, Velocity);

	SweeperSprite.setRotation(Orientation);
}

void Sweeper::Movement()
{
	Velocity *= Speed;
	Position += Velocity;
	SweeperSprite.setPosition(Position);
}

bool Sweeper::CheckBounds()
{
	Vector2f Min = Vector2f(Target.x - 2, Target.y - 2);
	Vector2f Max = Vector2f(Target.x + 2, Target.y + 2);
	if ((Position.x >= Min.x && Position.x <= Max.x) &&
		(Position.y >= Min.y && Position.y <= Max.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Sweeper::DecreaseLives()
{
	Lives--;

	if (Lives <= 0)
	{
		Alive = false;
	}
}
