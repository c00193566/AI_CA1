#pragma once
#include "GraphNode.h"

using namespace std;

typedef GraphNode<pair<string, int>, int> Node;

class SearchCostComparer {
public:
	bool operator()(Node * n1, Node * n2)
	{
		pair<string, int> p1 = n1->data();
		pair<string, int> p2 = n2->data();

		return p1.second > p2.second;
	}
};