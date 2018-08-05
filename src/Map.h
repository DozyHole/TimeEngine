#pragma once

class Point
{
public:
	Point() {};
	Point(float x, float y) : _x(x), _y(y) {}
	~Point() {}
	float	_x;
	float	_y;
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


class Map
{
public:
	Map();
	~Map();

	void DrawNodes();
	Point GetPosition(int index);


protected:
	short _width;
	short _height;
	float _spacing;

	Point _points[10][10];
};

