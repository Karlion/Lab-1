#pragma once
#include"Figure.h"

class Prism :public Figure
{
public:
	Position alpha;
public:
	Prism(std::vector<Position>, Position);
	~Prism(){};
	void DrawFigure();
};
