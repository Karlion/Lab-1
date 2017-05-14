#include "Prism.h"
#include<cmath>
#include<algorithm>

Prism::Prism(std::vector<Position>points, Position _alpha)
	:Figure(), alpha(_alpha)
{
	std::sort(points.begin(), points.end(), [](Position a, Position b){
		return atan2(a.x, a.z) < atan2(b.x, b.z);
	});
	_points = points;
	for (int i(0); i < points.size(); i++)
	{
		_points[i].y = 0;
		_top_points.push_back(Position(_points[i] + alpha));
	}
}

void Prism::DrawFigure(){
	glColor3f(_color.r, _color.g, _color.b);
	if (selected) glLineWidth(3); else glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (auto it : _points)
		glVertex3d(it.x, it.y, it.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (auto it : _top_points)
		glVertex3d(it.x, it.y, it.z);
	glEnd();

	glBegin(GL_LINES);
	for (int i(_points.size() - 1); i >= 0; i--)
	{
		glVertex3d(_points[i].x, _points[i].y, _points[i].z);
		glVertex3d(_top_points[i].x, _top_points[i].y, _top_points[i].z);
	}
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0x00F5);
	glLineWidth(1.5);
	for (auto it : projections) {
		glBegin(GL_LINE_LOOP);
		for (auto it0 : it)
			glVertex3d(it0.x, it0.y, it0.z);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(2);
}