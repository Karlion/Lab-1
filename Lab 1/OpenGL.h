#pragma once 
#include "Prism.h" 
#include "Cylinder.h" 
#include"Projection.h"

class OpenGL
{
private:
	double Window_Size, Window_Height;
public:

	OpenGL();
	~OpenGL();
	void Initialize();
	static void Draw();
	static void ActionFunc(unsigned char, int, int);
	static void RenderScene();
	static void LookAt(int, int, int);
	static void Mouse(int, int, int, int);
};
