#pragma once
#include "micropather.h"

#define MAP_WIDTH	125
#define MAP_HEIGHT	100
#define MAP_SIZE MAP_WIDTH*MAP_HEIGHT
class Point
{
public:
	Point() {};
	Point(float x, float y) : _x(x), _y(y) {}
	~Point() {}
	float	_x;
	float	_y;
	int*	_state;
};

class Point3
{
public:
	Point3() {};
	Point3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
	~Point3() {}
	float	_x;
	float	_y;
	float   _z;
};

class Map;

class CGraph : public micropather::Graph
{
public:
	CGraph(Map* map);
	~CGraph();

	/**
	Return the least possible cost between 2 states. For example, if your pathfinding
	is based on distance, this is simply the straight distance between 2 points on the
	map. If you pathfinding is based on minimum time, it is the minimal travel time
	between 2 points given the best possible terrain.
	*/
	virtual float LeastCostEstimate(void* stateStart, void* stateEnd) override;

	/**
	Return the exact cost from the given state to all its neighboring states. This
	may be called multiple times, or cached by the solver. It *must* return the same
	exact values for every call to MicroPather::Solve(). It should generally be a simple,
	fast function with no callbacks into the pather.
	*/
	virtual void AdjacentCost(void* state, std::vector< micropather::StateCost > *adjacent) override;

	/**
	This function is only used in DEBUG mode - it dumps output to stdout. Since void*
	aren't really human readable, normally you print out some concise info (like "(1,2)")
	without an ending newline.
	*/
	virtual void  PrintStateInfo(void* state) override;

protected:
	Map* _map;

};

class Map
{
public:
	Map();
	~Map();

	void DrawNodes();
	Point GetPosition(int index);

	std::vector<void*> GetPath(int iStart, int iEnd);

protected:
	short _width;
	short _height;
	float _spacing;

	micropather::MicroPather* _mp;
	Point _points[MAP_WIDTH][MAP_HEIGHT];
public:
	std::vector<int*> _states;
};

