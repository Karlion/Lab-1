#pragma once

#include <AntTweakBar.h>

#include "OpenGL.h"

namespace ATB
{
	static TwStructMember Coordinates_TW[] = {
		{ "x", TW_TYPE_DOUBLE, offsetof(Position, x), "step=10 min=-1000 max=1000" },
		{ "y", TW_TYPE_DOUBLE, offsetof(Position, y), "step=10 min=-1000 max=1000" },
		{ "z", TW_TYPE_DOUBLE, offsetof(Position, z), "step=10 min=-1000 max=1000" }
	};
	static TwStructMember Choose_projection[] = {
		{ "On X", TW_TYPE_BOOLCPP, offsetof(Projection::Pr_struct, _x), " true='Make' false='-' " },
		{ "On Y", TW_TYPE_BOOLCPP, offsetof(Projection::Pr_struct, _y), " true='Make' false='-' " },
		{ "On Z", TW_TYPE_BOOLCPP, offsetof(Projection::Pr_struct, _z), " true='Make' false='-' " }
	};



	static TwBar *bar;
	//settings
	static float color3F_TW[] = { 0.0, 0.0, 0.0};
	static double d_step_TW, d_angle_TW, d_zoom_TW;
	//static Color color_TW;

	//projection
	static Projection::Pr_struct Pr_type_TW(0, 0, 0);

	//cylinder
	static double height_TW,
		radius_TW;
	//prism
	static std::vector<Position> points_TW;
	static Position angle_TW,
		temp_point;
	static unsigned number_points_TW(0);

	void Initialize();
	void Reshape(int, int);
	void Registration();
	void AntTweak_Menu();
	void Stop_TW();

	void Menu_Figure();
	void Menu_Cylinder();
	void Menu_Prism();
	void Menu_Projection();
	void Menu_Settings();
	//void Menu_DB();

	void TW_CALL SetCallback(const void *, void *);
	void TW_CALL GetCallback_Settings(void*);
	//void TW_CALL GetCallback_DataBase(void*);
	//void TW_CALL SetCallback_DataBase(void*);
	void TW_CALL Callback_Figure_Delete(void*);
	void TW_CALL Callback_Projection_Delete(void*);

	void TW_CALL GetCallback_Pr(void*);
	void TW_CALL GetCallback_Cylinder(void*);
	void TW_CALL GetCallback_Prism(void*);
	void TW_CALL Callback_Point(void*);
};