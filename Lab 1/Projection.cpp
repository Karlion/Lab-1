#include"Projection.h"


/*void Projection::DrawFigure(){
glColor3f(color.r, color.g, color.b);
if (selected) glLineWidth(3); else glLineWidth(2);
glBegin(GL_LINE_LOOP);
for (auto it : points)
glVertex3d(it.x, it.y, it.z);
glEnd();
glLineWidth(2);
}

bool cmp(point a, point b) {
return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(point a, point b, point c) {
return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
}

bool ccw(point a, point b, point c) {
return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0;
}

void convex_hull(vector<point> & a) {
if (a.size() == 1)  return;
sort(a.begin(), a.end(), &cmp);
point p1 = a[0], p2 = a.back();
vector<point> up, down;
up.push_back(p1);
down.push_back(p1);
for (size_t i = 1; i<a.size(); ++i) {
if (i == a.size() - 1 || cw(p1, a[i], p2)) {
while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
up.pop_back();
up.push_back(a[i]);
}
if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
down.pop_back();
down.push_back(a[i]);
}
}
a.clear();
for (size_t i = 0; i<up.size(); ++i)
a.push_back(up[i]);
for (size_t i = down.size() - 2; i>0; --i)
a.push_back(down[i]);
}

void convert(Figure* figure, vector<point>&points, int val){
point temp;
if (val == 1){
for (auto &it:figure->_points){
temp.x = it.y;
temp.y = it.z;
points.push_back(temp);
}
for (auto &it : figure->_top_points){
temp.x = it.y;
temp.y = it.z;
points.push_back(temp);
}
}
else if (val == 2){
for (auto &it : figure->_points){
temp.x = it.x;
temp.y = it.z;
points.push_back(temp);
}
for (auto &it : figure->_top_points){
temp.x = it.x;
temp.y = it.z;
points.push_back(temp);
}
}
else{
for (auto &it : figure->_points){
temp.x = it.x;
temp.y = it.y;
points.push_back(temp);
}
for (auto &it : figure->_top_points){
temp.x = it.x;
temp.y = it.y;
points.push_back(temp);
}
}
}

void convert_back(Projection *temp, vector<point>&points, int val){
Position pos;
if (val == 1){
for (auto it : points){
pos.x = 0;
pos.y = it.x;
pos.z = it.y;
temp->points.push_back(pos);
}
}
else if (val == 2){
for (auto it : points){
pos.y = 0;
pos.x = it.x;
pos.z = it.y;
temp->points.push_back(pos);
}
}
else{
for (auto it : points){
pos.z = 0;
pos.x = it.x;
pos.y = it.y;
temp->points.push_back(pos);
}
}
}*/
#include "Projection.h"

void Projection::make_Projection(Figure* figure,
	const Pr_struct& input)

{
	make = input;

	std::vector<Position> mass;
	for (auto it : figure->_points)
		mass.push_back(it);
	for (auto it : figure->_top_points)
		mass.push_back(it);

	make_shell(mass);

	figure->projections.push_back(mass);
};
void Projection::make_shell(std::vector<Position>& mass)
{
	std::vector<Graham_shell::Point> new_mass;

	convert_Forward(mass, new_mass);
	Graham_shell::build_Graham_shell(new_mass);
	convert_Back(mass, new_mass);
};
void Projection::convert_Forward(std::vector<Position>& mass, std::vector<Graham_shell::Point>& new_mass)
{
	for (auto &it : mass) {
		if (!make._x) it.x = 0;
		if (!make._y) it.y = 0;
		if (!make._z) it.z = 0;
		if (!make._x) {
			new_mass.push_back(Graham_shell::Point(it.y, it.z));
			continue;
		}
		if (!make._y) {
			new_mass.push_back(Graham_shell::Point(it.x, it.z));
			continue;
		}
		if (!make._z) {
			new_mass.push_back(Graham_shell::Point(it.x, it.y));
			continue;
		}
	}
};
void Projection::convert_Back(std::vector<Position>& mass, const std::vector<Graham_shell::Point>& new_mas)
{
	mass.clear();
	if (!make._x) {
		for (auto it : new_mas)
			mass.push_back(Position(0, it.x, it.y));
		return;
	}
	if (!make._y) {
		for (auto it : new_mas)
			mass.push_back(Position(it.x, 0, it.y));
		return;
	}
	if (!make._z) {
		for (auto it : new_mas)
			mass.push_back(Position(it.x, it.y, 0));
		return;
	}

	for (size_t i = mass.size() - 1; i > 0; i--)
		if (mass[i] == mass[i - 1])
			mass.erase(mass.begin() + i);
};
