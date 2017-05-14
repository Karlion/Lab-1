/*#include"Figure.h"
#include<algorithm>
using namespace std;
class Projection :public Figure
{
public:
vector<Position> points;
Color color;
bool _x, _y, _z;
Projection(bool x,bool y,bool z) :color({ 12, 1, 3 }), _x(x),_y(y),_z(z){};
virtual void DrawFigure();
friend void convert_back(Projection*temp, vector<point>&points, int);
};



bool cmp(point a, point b);
bool cw(point a, point b, point c);
bool ccw(point a, point b, point c);
void convex_hull(vector<point> & a);*/
#pragma once
#include "Figure.h"
#include <algorithm>
#include <cmath>
#include "Graham.h"

namespace Projection
{
	struct Pr_struct{
		bool _x;
		bool _y;
		bool _z;
		Pr_struct(bool i_x, bool i_y, bool i_z) :
			_x(i_x), _y(i_y), _z(i_z) {};
	};

	void make_shell(std::vector<Position>&);
	void convert_Forward(std::vector<Position>&, std::vector<Graham_shell::Point>&);
	void convert_Back(std::vector<Position>&, const std::vector<Graham_shell::Point>&);

	static Pr_struct make(0, 0, 0);

	void make_Projection(Figure*, const Pr_struct&);

};
