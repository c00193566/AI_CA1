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

	CurrentState = States::Setup;

	Start = -1000;
	End = -1000;

	Path = vector<Node*>();
}

Worker::~Worker()
{

}

void Worker::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(WorkerSprite);
}

void Worker::Update(unsigned int DT, Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * Waypoints)
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
		cout << "Searching..." << endl;

		// Not in Range, generate random index
		int Point = rand() % Waypoints->size();
		End = Path::NearestPointIndex(Waypoints, Position);

		// Don't want to go to last point
		if (Point != End)
		{
			Start = Path::NearestPointIndex(Waypoints, Position);
			End = Point;
			Path = Path::UniformCostSearch(GraphData, Waypoints, Start, End);
			cout << Start << " , " << End << endl;
			CurrentState = States::FollowPath;
		}
	}
	else if (CurrentState == States::FollowPath)
	{

		// Check if reached endpoint
		if (Start == End)
		{
			cout << "Location : " << Position.x << " , " << Position.y << endl;
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
	}

	Movement();
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

bool Worker::CheckBounds()
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