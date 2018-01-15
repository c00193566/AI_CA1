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
}

Sweeper::~Sweeper()
{
	
}

void Sweeper::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(SweeperSprite);
}

void Sweeper::Update(unsigned int DT, Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * Waypoints, vector<Enemy*> * WorkerPos)
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

		// check if Worker comes into range
		float Dis;

		if (WorkerPos->size() > 0)
		{
			for (int i = 0; i < WorkerPos->size(); i++)
			{
				Vector2f Dir = WorkerPos->at(i)->getPosition() - Position;
				Dis = Vector::Length(Dir);
			}
		}

		if (Dis < MaxRange)
		{
			CurrentState = States::Search;
			return;
		}

		//check if reached endpoint
		if (Start == End || Dis < MinRange)
		{
			if (WorkerPos->size() > 0)
			{
				for (int i = 0; WorkerPos->size(); i++)
				{
					Target = WorkerPos->at(i)->getPosition();
				}
			}
			else
			{
				CurrentState = States::Search;
			}
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