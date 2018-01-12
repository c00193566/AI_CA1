#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	EnemyTexture = LoadedTexture;

	EnemySprite.setTexture(EnemyTexture);

	EnemySprite.setOrigin(8.0f, 8.0f);

	Position = Vector2f(x, y);
	EnemySprite.setPosition(Position);

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 1.0f;

	Range = 0;

	CurrentState = States::Search;

	Start = -1000;
	End = -1000;

	Path = vector<Node*>();
}

Enemy::~Enemy()
{

}

void Enemy::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(EnemySprite);
}

void Enemy::Update(unsigned int DT, Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * WayPoints, Vector2f PlayerPos)
{
	if (CurrentState == States::Search)
	{
		cout << "Searching..." << endl;
		// Is Player in range?
		Vector2f Dir = PlayerPos - Position;
		float Dis = Vector::Length(Dir);
		if (Dis < Range)
		{
			Start = Path::NearestPointIndex(WayPoints, Position);
			End = Path::NearestPointIndex(WayPoints, PlayerPos);
			CurrentState = States::FollowPlayer;
		}
		else
		{
			// Not in Range, generate random index
			int Point = rand() % WayPoints->size();

			// Don't want to go to last point
			if (Point != End)
			{
				Start = Path::NearestPointIndex(WayPoints, Position);
				End = Point;
				Path = Path::UniformCostSearch(GraphData, WayPoints, Start, End);
				cout << Start << " , " << End << endl;
				CurrentState = States::FollowPath;
			}
		}
	}
	else if (CurrentState == States::FollowPath)
	{

		// Check if reached endpoint
		if (Start == End)
		{
			cout << "Location : " << Position.x << " , " << Position.y << endl;
			CurrentState = States::Search;
		}

		else
		{
			if (Path.size() > 0)
			{
				string PointName = Path.at(Path.size() - 1)->data().first;
				int PointIndex = stoi(PointName);
				Target = WayPoints->at(PointIndex);

				if (CheckBounds())
				{
					Start = Path::NearestPointIndex(WayPoints, Position);
					Path.pop_back();
				}
			}
		}

		// Check if comes into range
		Vector2f Dir = PlayerPos - Position;
		float Dis = Vector::Length(Dir);		
		if (Dis < Range)
		{
			CurrentState = States::Search;
		}
	}
	else if (CurrentState == States::FollowPlayer)
	{
		// Check if reached endpoint
		if (Start == End)
		{
			Target = PlayerPos;
		}
		else
		{
			//Target = Path::UniformCostSearch(GraphData, WayPoints, Start, End);

			if (CheckBounds())
			{
				Start = Path::NearestPointIndex(WayPoints, Position);
			}
		}

		// Check if comes into range
		Vector2f Dir = PlayerPos - Position;
		float Dis = Vector::Length(Dir);
		if (Dis > Range)
		{
			CurrentState = States::Search;
		}
	}

	Seek();
	Movement();
}

void Enemy::Movement()
{
	Position += Velocity;
	EnemySprite.setPosition(Position);
}

void Enemy::Seek()
{
	Velocity = Target - Position;

	Velocity = Vector::Normalise(Velocity);

	Velocity *= Speed;

	Orientation = Vector::GetOrientation(Orientation, Velocity);

	EnemySprite.setRotation(Orientation);
}

bool Enemy::CheckBounds()
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
