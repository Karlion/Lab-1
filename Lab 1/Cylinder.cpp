#include"Cylinder.h"

void Cylinder::DrawFigure(){

	glColor3f(_color.r, _color.g, _color.b);
	if (selected) glLineWidth(3); else glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (auto it : this->_points)
		glVertex3d(it.x, it.y, it.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (auto it : this->_top_points)
		glVertex3d(it.x, it.y, it.z);
	glEnd();
	glBegin(GL_LINES);
	for (int i(this->_points.size() - 1); i >= 0; i -= _points.size() / 10){
		glVertex3d(this->_points[i].x, this->_points[i].y, this->_points[i].z);
		glVertex3d(this->_top_points[i].x, this->_top_points[i].y, this->_top_points[i].z);
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