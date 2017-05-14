#include "Figure.h"

void changeAngle(Figure* figure, int d_x, int d_y, int d_z){
	float cos_val = cos(figure->d_angle*atan(1.0) * 4 / 180),
		sin_val = sin(figure->d_angle*atan(1.0) * 4 / 180);
	Position cent = figure->center;
	for (auto &it : figure->_points){
		Position temp = it;
		if (d_x){
			it.y = temp.y*cos_val + temp.z*sin_val*d_x;
			it.z = -temp.y*sin_val*d_x + temp.z*cos_val;
		}
		if (d_y){
			it.x = temp.x*cos_val + temp.z*sin_val*d_y;
			it.z = -temp.x*sin_val*d_y + temp.z*cos_val;
		}
		if (d_z){
			it.x = temp.x*cos_val - temp.y*sin_val*d_z;
			it.y = temp.x*sin_val*d_z + temp.y*cos_val;
		}
	}
	for (auto &it : figure->_top_points){
		Position temp = it;
		if (d_x){
			it.y = temp.y*cos_val + temp.z*sin_val*d_x;
			it.z = -temp.y*sin_val*d_x + temp.z*cos_val;
		}
		if (d_y){
			it.x = temp.x*cos_val + temp.z*sin_val*d_y;
			it.z = -temp.x*sin_val*d_y + temp.z*cos_val;
		}
		if (d_z){
			it.x = temp.x*cos_val - temp.y*sin_val*d_z;
			it.y = temp.x*sin_val*d_z + temp.y*cos_val;
		}
	}
	if (d_x){
		figure->center.y = cent.y*cos_val + cent.z*sin_val*d_x;
		figure->center.z = -cent.y*sin_val*d_x + cent.z*cos_val;
	}
	if (d_y){
		figure->center.x = cent.x*cos_val + cent.z*sin_val*d_y;
		figure->center.z = -cent.x*sin_val*d_y + cent.z*cos_val;
	}
	if (d_z){
		figure->center.x = cent.x*cos_val - cent.y*sin_val*d_z;
		figure->center.y = cent.x*sin_val*d_z + cent.y*cos_val;
	}
}

void changePosition(Figure*figure, int d_x, int d_y, int d_z){
	for (auto &it : figure->_points){
		if (d_x){
			it.x += figure->d_step*d_x;
		}
		if (d_y){
			it.y += figure->d_step*d_y;
		}
		if (d_z){
			it.z += figure->d_step*d_z;
		}
	}
	for (auto &it : figure->_top_points){
		if (d_x){
			it.x += figure->d_step*d_x;
		}
		if (d_y){
			it.y += figure->d_step*d_y;
		}
		if (d_z){
			it.z += figure->d_step*d_z;
		}
	}
	if (d_x){
		figure->center.x += figure->d_step*d_x;
	}
	if (d_y){
		figure->center.y += figure->d_step*d_y;
	}
	if (d_z){
		figure->center.z += figure->d_step*d_z;
	}
}

void changeSize(Figure* figure, bool zoom){
	if (zoom){
		for (auto &it : figure->_points){
			it = it - figure->center;
			it.x *= 1.0 + figure->d_zoom;
			it.y *= 1.0 + figure->d_zoom;
			it.z *= 1.0 + figure->d_zoom;
			it = it + figure->center;
		}
		for (auto &it : figure->_top_points){
			it = it - figure->center;
			it.x *= 1.0 + figure->d_zoom;
			it.y *= 1.0 + figure->d_zoom;
			it.z *= 1.0 + figure->d_zoom;
			it = it + figure->center;
		}
	}
	else{
		for (auto &it : figure->_points){
			it = it - figure->center;
			it.x *= 1.0 - figure->d_zoom;
			it.y *= 1.0 - figure->d_zoom;
			it.z *= 1.0 - figure->d_zoom;
			it = it + figure->center;
		}
		for (auto &it : figure->_top_points){
			it = it - figure->center;
			it.x *= 1.0 - figure->d_zoom;
			it.y *= 1.0 - figure->d_zoom;
			it.z *= 1.0 - figure->d_zoom;
			it = it + figure->center;
		}
	}
}