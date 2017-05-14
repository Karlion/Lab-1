#pragma once
#include<GL\freeglut.h>
#include"Position.h"
struct Color{
	double r;
	double g;
	double b;
	void operator ()(const double _r, const double _g, const double _b){
		this->r = _r;
		this->g = _g;
		this->b = _b;
	}
};


class Figure
{
public:
	Color _color;
	float d_zoom;
	float d_angle;
	float d_step;
	bool selected;
	Position center;
	std::vector<Position> _points;
	std::vector<Position> _top_points;
	std::vector< std::vector<Position>> projections;
	virtual ~Figure(){};
	Figure(Color color = Color{ 1, 1, 0 }) :selected(false), _color(color), d_angle(3),
		d_step(3), center(0, 0, 0), d_zoom(0.05){};
	virtual void DrawFigure() = 0;
	friend void changeAngle(Figure*, int, int, int);
	friend void changePosition(Figure*, int, int, int);
	friend void changeSize(Figure*, bool);
};
static std::vector<Figure*> figures;