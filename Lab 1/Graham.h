#pragma once;
#include <vector>
#include <algorithm>

namespace Graham_shell
{
	struct Point
	{
		double x, y;
		Point(double _x, double _y) : x(_x), y(_y){};
	};
	double triangle_area(const Point &, const Point &, const Point &);

	void build_Graham_shell(std::vector<Point> &);
};