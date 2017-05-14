#pragma once
#include<vector>
#include<iostream>

struct Position{
	double x;
	double y;
	double z;
	//void operator()(float, float, float);
	Position(float _x = 0, float _y = 0, float _z = 0) :x(_x), y(_y), z(_z){}
	Position(const Position&input) :x(input.x), y(input.y), z(input.z){};
	Position operator +(const Position &pos){
		return Position(this->x + pos.x, this->y + pos.y, this->z + pos.z);
	}
	Position operator -(const Position &pos){
		return Position(this->x - pos.x, this->y - pos.y, this->z - pos.z);
	}
	Position operator *(const int value){
		return Position(this->x*value, this->y*value, this->z*value);
	}
	friend bool operator== (const Position& a, const Position& b){
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
	}
};