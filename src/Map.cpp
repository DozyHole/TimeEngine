#include "Map.h"
#include "agk.h"

Map::Map()
{
	_width			= 10;
	_height			= 10;
	_spacing		= 75.0f;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_points[x][y] = Point(x * _spacing + _spacing/2.0f, y * _spacing + _spacing/2.0f);
		}
	}
}

Map::~Map()
{
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
			agk::DrawEllipse(_points[x][y]._x, _points[x][y]._y, 5.0f, 5.0f, colour, colour, 1);
		}
	}
}
