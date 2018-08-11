#include "Map.h"
#include "agk.h"

CGraph::CGraph(Map* map)
{
	_map = map;
}

CGraph::~CGraph() {}

float CGraph::LeastCostEstimate(void* stateStart, void* stateEnd)
{
	// distance between the two points
	int iStart			= *(int*)stateStart;
	int iEnd			= *(int*)stateEnd;
	Point pStart		= _map->GetPosition(iStart);
	Point pEnd			= _map->GetPosition(iEnd);
	float xDiff			= pEnd._x - pStart._x;
	float yDiff			= pEnd._y - pStart._y;
	float distSquared	= xDiff*xDiff + yDiff*yDiff;
	return distSquared;
}

void CGraph::AdjacentCost(void* state, std::vector< micropather::StateCost > *adjacent)
{
	int index = *(int*)state;
	// up
	int uIndex = index - MAP_WIDTH;
	if (uIndex >= 0)
	{
		// we have an above
		micropather::StateCost sc;
		_map->GetPosition(uIndex)._state;
		sc.state	= (void*)_map->GetPosition(uIndex)._state;
		sc.cost		= 1;	
		(*adjacent).push_back(sc);
	}

	// down
	int dIndex = index + MAP_WIDTH;
	if (dIndex < MAP_SIZE)
	{
		// we have a below
		micropather::StateCost sc;
		sc.state = (void*)_map->GetPosition(dIndex)._state;
		sc.cost = 1;
		(*adjacent).push_back(sc);
	}

	// left 
	if (index % MAP_WIDTH != 0)
	{
		// we have a left
		micropather::StateCost sc;
		sc.state = (void*)_map->GetPosition(index-1)._state;
		sc.cost = 1;
		(*adjacent).push_back(sc);
	}

	// right
	if ((index + 1) % MAP_WIDTH != 0)
	{
		// we have a right
		micropather::StateCost sc;
		int st = *_map->GetPosition(index + 1)._state;
		sc.state = (void*)_map->GetPosition(index+1)._state;
		sc.cost = 1;
		(*adjacent).push_back(sc);
	}
}

void CGraph::PrintStateInfo(void* state)
{

}





Map::Map()
{
	_mp				= new micropather::MicroPather(new CGraph(this));
	_width			= MAP_WIDTH;
	_height			= MAP_HEIGHT;
	_spacing		= 7.0f;

	int index = 0;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			// micropather - requires state pointers
			int* state = new int();
			*state = index;
			//_states.push_back(state);
			_points[x][y] = Point(x * _spacing + _spacing/2.0f, y * _spacing + _spacing/2.0f);
			_points[x][y]._state = state;
			index++;
		}
	}
}

Map::~Map()
{
	//for (int i = 0; i < _states.size(); i++)
	//{
	//	delete _states.at(i);
	//	_states.at(i) = nullptr;
	//}
	//_states.clear();
}

std::vector<void*> Map::GetPath(int iStart, int iEnd)
{
	std::vector<void*> pathOut;
	float costOut;
	void* s = (void*)GetPosition(iStart)._state;
	void* e = (void*)GetPosition(iEnd)._state;
	int success = _mp->Solve(s, e, &pathOut, &costOut);
	micropather::MicroPather::SOLVED;
	micropather::MicroPather::NO_SOLUTION;
	micropather::MicroPather::START_END_SAME;

	return pathOut;
}

Point Map::GetPosition(int index)
{
	int x = index % _width;
	int y = index / _width;
	return _points[x][y];
}

void Map::DrawNodes()
{
	int colour = 255 | 255 << 8 | 255 << 16 | 255 << 24;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			agk::DrawEllipse(_points[x][y]._x, _points[x][y]._y, 1.0f, 1.0f, colour, colour, 1);
		}
	}
}