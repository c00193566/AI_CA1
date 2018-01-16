#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "GameObject.h"

/**
* \struct Path
*
* \brief static methods to be called by AI
*
* This struct allows the AI to call the needed
* methods to interact with the waypoints.
*
* \author $Author: Jack Keogh $
*/

using namespace std;
using namespace sf;

typedef GraphArc<string, int> Arc;
typedef GraphNode<pair<string, int>, int> Node;

struct Path
{
	/**
	 * \brief Searches for the nearest Waypoint and returns it.
	 * \param Points a vector<Vector2f> pointer to the Waypoints memory location.
	 * \param Position a Vector2f variable of an object's position
	 *
	 * This method searches for the closest waypoint by looping through the waypoints
	 * and checking the distance between the waypoints position and the position passed
	 * in. Once it finds the closest distance it assigns an integer the index value of 
	 * the waypoint. Once out of the loop it returns the waypoint at the index value.
	 */
	static Vector2f NearestPointPosition(vector<Vector2f> * Points, Vector2f Position);

	/**
	 * \bried Searches for the index value of the nearest waypoint and returns it
	 * \param Points a vector<Vector2f> pointer to the Waypoints memory location.
	 * \param Position a Vector2f variable of an object's position
	 *
	 * This method searches for the closest waypoint index by looping through the waypoints
	 * and checking the distance between the waypoints position and the position passed
	 * in. Once it finds the closest distance it assigns an integer the index value of 
	 * the waypoint. Once out of the loop it returns the index value.
	 */
	static int NearestPointIndex(vector<Vector2f> * Points, Vector2f Position);

	/**
	 * \brief Uses UCS to find a path and return it.
	 * \param GraphData Graph<pair<string, int>, int> pointer to the graph's memory location.
	 * \param Points a vector<Vector2f> pointer to the Waypoints memory location.
	 * \param Start a integer value to indicate the starting node of the path.
	 * \param End a integer value to indicate the ending node of the path.
	 *
	 * This method creates a local variable of vector<Node *> called path. Graphdata
	 * calls its ucs method passing in the start node, the end node and the local
	 * path variable. The path variable will get populated within the ucs method.
	 * If the size of the path is 0 then a default vector<Node*> will be returned
	 * else the path will be returned.
	 */
	static vector<Node*> UniformCostSearch(Graph<pair<string, int>, int> * GraphData, vector<Vector2f> * Points, int Start, int End);

};