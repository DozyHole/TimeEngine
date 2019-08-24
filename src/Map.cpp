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
	int iStart			= (int)stateStart;
	int iEnd			= (int)stateEnd;
	Point pStart		= _map->GetPosition(iStart);
	Point pEnd			= _map->GetPosition(iEnd);
	float xDiff			= pEnd._x - pStart._x;
	float yDiff			= pEnd._y - pStart._y;
	float distSquared	= xDiff*xDiff + yDiff*yDiff;
	return distSquared;
}

void CGraph::AdjacentCost(void* state, std::vector< micropather::StateCost > *adjacent)
{
	int index = (int)state;
	// up
	int uIndex = index - MAP_WIDTH;
	if (uIndex >= 0)
	{
		// we have an above
		micropather::StateCost sc;
		//_map->GetPosition(uIndex)._state;
		Point p = _map->GetPosition(uIndex);
		if (!p._blocked)
		{
			sc.state = (void*)p._state;
			sc.cost = 1;
			(*adjacent).push_back(sc);
		}
	}

	// down
	int dIndex = index + MAP_WIDTH;
	if (dIndex < MAP_SIZE)
	{
		// we have a below
		micropather::StateCost sc;
		Point p = _map->GetPosition(dIndex);
		if (!p._blocked)
		{
			sc.state = (void*)p._state;
			sc.cost = 1;
			(*adjacent).push_back(sc);
		}
	}

	// left 
	if (index % MAP_WIDTH != 0)
	{
		// we have a left
		micropather::StateCost sc;
		Point p = _map->GetPosition(index-1);
		if (!p._blocked)
		{
			sc.state = (void*)p._state;
			sc.cost = 1;
			(*adjacent).push_back(sc);
		}
	}

	// right
	if ((index + 1) % MAP_WIDTH != 0)
	{
		// we have a right
		micropather::StateCost sc;
		//int st = *_map->GetPosition(index + 1)._state;
		Point p = _map->GetPosition(index+1);
		if (!p._blocked)
		{
			sc.state = (void*)p._state;
			sc.cost = 1;
			(*adjacent).push_back(sc);
		}
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
			//int* state = new int();
			//*state = index;
			//_states.push_back(state);
			_points[x][y] = Point(x * _spacing + _spacing/2.0f, y * _spacing + _spacing/2.0f);
			_points[x][y]._state = index;

			// add to blocked and non blocked
			_points[x][y]._blocked ? _vecBlockedPoints.push_back(index) : _vecNonBlockedPoints.push_back(index);

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

int Map::GetNonBlockedPointRand()
{
	int count = _vecNonBlockedPoints.size();
	int index = rand() % count;
	return _vecNonBlockedPoints.at(index);
}

const std::vector<void*> Map::GetPath(int iStart, int iEnd, float *costOut)
{
	std::vector<void*> pathOut;
	//float costOut;
	void* s = (void*)GetPosition(iStart)._state;
	void* e = (void*)GetPosition(iEnd)._state;
	int success = _mp->Solve(s, e, &pathOut, costOut);
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

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			int colour = 255 | 255 << 8 | 255 << 16 | 255 << 24;
			Point p = _points[x][y];
			if (p._blocked)
			{
				colour = 255 | 0 << 8 | 0 << 16 | 255 << 24;
				agk::DrawEllipse(p._x, p._y, 2.0f, 2.0f, colour, colour, 1);
			}
			//agk::DrawEllipse(p._x, p._y, 2.0f, 2.0f, colour, colour, 1);
		}
	}
}
