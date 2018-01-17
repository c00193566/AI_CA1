#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	EnemyTexture = LoadedTexture;

	EnemySprite.setTexture(EnemyTexture);

	EnemySprite.setOrigin(EnemyTexture.getSize().x / 2, EnemyTexture.getSize().y / 2);

	Position = Vector2f(x, y);
	EnemySprite.setPosition(Position);

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 1.0f;

	MaxRange = 128;
	MinRange = 32;

	CurrentState = States::Setup;

	Start = -1000;
	End = -1000;

	Path = vector<Node*>();

	Lives = 3;

	Alive = true;
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
	if (CurrentState == States::Setup)
	{
		Target = Path::NearestPointPosition(WayPoints, Position);

		if (CheckBounds())
		{
			CurrentState = States::Search;
		}
	}
	else if (CurrentState == States::Search)
	{
		// Is Player in range?
		Vector2f Dir = PlayerPos - Position;
		float Dis = Vector::Length(Dir);
		if (Dis < MaxRange)
		{
			Start = Path::NearestPointIndex(WayPoints, Position);
			End = Path::NearestPointIndex(WayPoints, PlayerPos);
			CurrentState = States::FollowPlayer;
		}
		else
		{
			// Not in Range, generate random index
			int Point = rand() % WayPoints->size();
			End = Path::NearestPointIndex(WayPoints, Position);

			// Don't want to go to last point
			if (Point != End)
			{
				Start = Path::NearestPointIndex(WayPoints, Position);
				End = Point;
				Path = Path::UniformCostSearch(GraphData, WayPoints, Start, End);
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
			Target = WayPoints->at(PointIndex);

			if (CheckBounds())
			{
				Start = Path::NearestPointIndex(WayPoints, Position);
				Path.pop_back();
			}
		}

		// Check if comes into range
		Vector2f Dir = PlayerPos - Position;
		float Dis = Vector::Length(Dir);

		if (Dis < MaxRange)
		{
			CurrentState = States::Search;
		}
	}
	else if (CurrentState == States::FollowPlayer)
	{
		// Check if comes into range
		Vector2f Dir = PlayerPos - Position;
		float Dis = Vector::Length(Dir);

		if (Dis > MaxRange)
		{
			CurrentState = States::Search;
			return;
		}

		// Check if reached endpoint
		if (Start == End || Dis < MinRange)
		{
			Target = PlayerPos;
		}

		if (Dis > MinRange)
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

void Enemy::DecreaseLives()
{
	Lives--;

	if (Lives <= 0)
	{
		Alive = false;
	}
}
