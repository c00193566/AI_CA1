#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "GameObject.h"

using namespace std;
using namespace sf;

typedef GraphArc<string, int> Arc;
typedef GraphNode<pair<string, int>, int> Node;

class Path
{
private:

public:
	Path();
	~Path();
	static Vector2f NearestPointPosition(vector<Vector2f> *, Vector2f);
	static int NearestPointIndex(vector<Vector2f> *, Vector2f);
	static Vector2f UniformCostSearch(Graph<pair<string, int>, int> *, vector<Vector2f> *, int, int);

};