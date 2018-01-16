#include "Path.h"

Vector2f Path::NearestPointPosition(vector<Vector2f>* Points, Vector2f Position)
{
	float CurrentMinDis = numeric_limits<int>::max() - 10000;
	int Index;

	for (int i = 0; i < Points->size(); i++)
	{
		Vector2f Dir = Points->at(i) - Position;
		float Distance = Vector::Length(Dir);

		if (Distance < CurrentMinDis)
		{
			CurrentMinDis = Distance;
			Index = i;
		}
	}

	return Points->at(Index);
}

int Path::NearestPointIndex(vector<Vector2f>* Points, Vector2f Position)
{
	float CurrentMinDis = numeric_limits<int>::max() - 10000;
	int Index;

	for (int i = 0; i < Points->size(); i++)
	{
		Vector2f Dir = Points->at(i) - Position;
		float Distance = Vector::Length(Dir);

		if (Distance < CurrentMinDis)
		{
			CurrentMinDis = Distance;
			Index = i;
		}
	}

	return Index;
}

vector<Node*> Path::UniformCostSearch(Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * Points,int Start, int Dest)
{
	vector<Node *> Path;

	GraphData->ucs(GraphData->nodeIndex(Start), GraphData->nodeIndex(Dest), Path);

	if (Path.size() > 0)
	{
		return Path;
	}
	else
	{
		return vector<Node*>();
	}
}
