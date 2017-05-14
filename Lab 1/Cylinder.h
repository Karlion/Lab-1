#pragma once
#include"Figure.h"

class Cylinder :public Figure
{
protected:
	float _radius;
	float _height;
	float d_x;
	Position _pos;
public:
	Cylinder(float height, float radius) :_radius(radius), _height(height), _pos(0, 0, 0),
		d_x(1)
	{
		for (float coordinate_x = -_radius; coordinate_x <= _radius; coordinate_x += d_x)
		{
			float coordinate_z = sqrt(_radius*_radius - coordinate_x * coordinate_x);
			_points.push_back(Position(coordinate_x, 0, coordinate_z));
			_points.insert(_points.begin(), Position(coordinate_x, 0, -coordinate_z));
			_top_points.push_back(Position(coordinate_x, _height, coordinate_z));
			_top_points.insert(_top_points.begin(), Position(coordinate_x, _height, -coordinate_z));
		}
	};
	virtual void DrawFigure();
};