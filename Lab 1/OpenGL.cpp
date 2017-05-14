#include<AntTweakBar.h>
#include"ATB.h"



double angle = 0.0;
OpenGL::OpenGL() : Window_Size(1000), Window_Height(800)
{
	/*std::vector<Position> v;
	v.push_back(Position(0, 0, 0));
	for (int i(0); i < 4; i++)
		v.push_back(Position(rand() % 100, i, rand() % 100));
	Position al(20, 45, 7);
	figures.push_back(new Prism(v, al));
	figures.push_back(new Cylinder(200, 100));*/

	int argc = 1;
	char *argv[1] = { (char*)"" };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Window_Size, Window_Height);
	glutInitWindowPosition(0, 0);
	glViewport(0, 0, 1000, 800);
	glutCreateWindow("3D-Figures");

	ATB::AntTweak_Menu();



	glutMouseFunc(Mouse);
	glutKeyboardFunc(ActionFunc);
	glutSpecialFunc(LookAt);
	glutDisplayFunc(Draw);
	Initialize();
	glutMainLoop();
};
void OpenGL::Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	gluPerspective(40, double(1.2), 1, 10000);
	gluLookAt(600.0, 600.0, 600.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};
void OpenGL::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 0, 0);
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -200.0, 0.0);
	glVertex3f(0.0, 500.0, 0.0);//y - green 
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200.0, 0.0, 0.0);
	glVertex3f(500.0, 0.0, 0.0);//x - red 
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -200.0);
	glVertex3f(0.0, 0.0, 500.0);//z - blue 
	glEnd();
	glPopMatrix();
	RenderScene();
	TwDraw();

	glutSwapBuffers();

};
void OpenGL::RenderScene() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	for (int i = 0; i < figures.size(); i++){

		glStencilFunc(GL_ALWAYS, i + 1, 0);
		figures[i]->DrawFigure();
	}
	glPopMatrix();
	glutPostRedisplay();
	//glLoadIdentity();
}
void OpenGL::Mouse(int button, int state, int x, int y)
{
	if (!TwEventMouseButtonGLUT(button, state, x, y)) {
		if (state != GLUT_DOWN)
			return;
		glClearStencil(0);

		GLuint index;
		glReadPixels(x, 800 - y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		if (index == 0) {
			for (auto &it : figures)
				it->selected = false;
		}
		else {
			if (figures[index - 1]->selected)
				figures[index - 1]->selected = false;
			else
				figures[index - 1]->selected = true;
		}
	}
};



OpenGL::~OpenGL()
{
}


void OpenGL::ActionFunc(unsigned char key, int x, int y)
{
	if (key == 27){
		for (auto it : figures)
			delete it;
		ATB::Stop_TW();
		exit(0);
	}
	for (int i = 0; i < figures.size(); i++){
		if (figures[i]->selected)
			switch (key) {
			case 127:
				delete figures[i];
				figures.erase(figures.begin() + i);
				break;
			case 'r':
				changeAngle(figures[i], 1, 0, 0);
				break;
			case 'f':
				changeAngle(figures[i], -1, 0, 0);
				break;
			case 't':
				changeAngle(figures[i], 0, 1, 0);
				break;
			case 'g':
				changeAngle(figures[i], 0, -1, 0);
				break;
			case 'y':
				changeAngle(figures[i], 0, 0, 1);
				break;
			case 'h':
				changeAngle(figures[i], 0, 0, -1);
				break;
			case 'd':
				changePosition(figures[i], 1, 0, 0);
				break;
			case 'q':
				changePosition(figures[i], -1, 0, 0);
				break;
			case 'w':
				changePosition(figures[i], 0, 1, 0);
				break;
			case 's':
				changePosition(figures[i], 0, -1, 0);
				break;
			case 'a':
				changePosition(figures[i], 0, 0, 1);
				break;
			case 'e':
				changePosition(figures[i], 0, 0, -1);
				break;
			case 'z':
				changeSize(figures[i], 1);
				break;
			case 'x':
				changeSize(figures[i], 0);
				break;
		}
	}
	glutPostRedisplay();
}


void OpenGL::LookAt(int key, int x, int y){
	switch (key){
	case GLUT_KEY_LEFT:
		glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		glRotatef(-1.0f, 0.0f, 1.0f, 0.0f);
		break;
	}
	glutPostRedisplay();
}


void ATB::Initialize()
{
	TwInit(TW_OPENGL, nullptr);
	TwWindowSize(1000, 800);
};
void ATB::Reshape(int width, int height)
{
	TwWindowSize(width, height);
};
void ATB::Registration()
{
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	TwGLUTModifiersFunc(glutGetModifiers);
};
void ATB::Stop_TW()
{
	TwTerminate();
};
void ATB::AntTweak_Menu()
{
	int igg = figures.size();

	ATB::Initialize();
	ATB::Registration();

	igg = figures.size();
	bar = TwNewBar("Menu");

	TwDefine(" Menu movable=false resizable=false color='96 10 100' size = '300 500'");
	TwDefine(" GLOBAL help='Play with 3D modeling!\n' ");
	TwDefine(" GLOBAL fontsize=3 ");


	Menu_Figure();
	TwAddSeparator(bar, nullptr, "");
	Menu_Settings();
	TwAddSeparator(bar, nullptr, "");
	//	Menu_DB();

};

void TW_CALL ATB::GetCallback_Settings(void*)
{
	for (auto &it : figures)
		if (it->selected) {
			it->d_angle = d_angle_TW;
			it->d_step = d_step_TW;
			it->d_zoom = d_zoom_TW;

			/*it->_color.r = color3F_TW[0];
			it->_color.g = color3F_TW[1];
			it->_color.b = color3F_TW[2];*/
			it->_color(color3F_TW[0], color3F_TW[1], color3F_TW[2]);
		}
};
/*void TW_CALL ATB_menu::SetCallback_DataBase(void*)
{
Data_Base::Insert(figures_to_paint);
};
void TW_CALL ATB_menu::GetCallback_DataBase(void*)
{
Data_Base::Download(figures_to_paint);
};*/
void TW_CALL ATB::Callback_Projection_Delete(void*)
{
	for (int i = figures.size() - 1; i >= 0; i--)
		if (figures[i]->selected &&
			!figures[i]->projections.empty())
			figures[i]->projections.pop_back();
};
void TW_CALL ATB::Callback_Figure_Delete(void*)
{
	for (int i = figures.size() - 1; i >= 0; i--)
		if (figures[i]->selected) {
			delete figures[i];
			figures.erase(figures.begin() + i);
		}
};
void TW_CALL ATB::GetCallback_Pr(void*)
{
	if (Pr_type_TW._x == Pr_type_TW._y &&
		Pr_type_TW._x == Pr_type_TW._z)
		return;

	for (int i = figures.size() - 1; i >= 0; i--)
		if (figures[i]->selected)
			Projection::make_Projection(figures[i],
			Pr_type_TW);
};
void TW_CALL ATB::GetCallback_Cylinder(void*)
{
	if (radius_TW > 0 && height_TW > 0)
		figures.push_back(new Cylinder(height_TW, radius_TW));
};
void TW_CALL ATB::GetCallback_Prism(void*)
{
	if (points_TW.empty())
		return;
	figures.push_back(new Prism(points_TW, angle_TW));
	points_TW.clear();
	angle_TW = (0, 0, 0);
	number_points_TW = 0;
};
void TW_CALL ATB::Callback_Point(void* insert)
{
	bool ans = static_cast<bool>(insert);
	if (ans) {
		points_TW.push_back(temp_point);
		number_points_TW++;
	}
	else
		if (!points_TW.empty()) {
			points_TW.pop_back();
			number_points_TW--;
		}
};

void ATB::Menu_Settings()
{
	TwAddVarRW(bar, "Color", TW_TYPE_COLOR3F, &color3F_TW,
		" group=Settings ");
	TwAddVarRW(bar, "Angle", TW_TYPE_DOUBLE, &d_angle_TW,
		" group=Settings value=2.0 min=0.0 max=6.0 step=0.1 ");
	TwAddVarRW(bar, "Step", TW_TYPE_DOUBLE, &d_step_TW,
		" group=Settings value=2.0 min=0.0 max=6.0 step=0.1 ");
	TwAddVarRW(bar, "Zoom", TW_TYPE_DOUBLE, &d_zoom_TW,
		" group=Settings value=0.1 min=0.0 max=0.35 step=0.01 ");
	TwAddButton(bar, "Save_settings", GetCallback_Settings, nullptr,
		" group=Settings label='Apply' ");
};
/*void ATB_menu::Menu_DB()
{
TwAddButton(bar, "Save", SetCallback_DataBase, nullptr,
" group=DataBase label='Save' ");
TwAddButton(bar, "Download", GetCallback_DataBase, nullptr,
" group=DataBase label='Download' ");
};*/
void ATB::Menu_Figure()
{
	TwAddButton(bar, "Delete", Callback_Figure_Delete, nullptr,
		" group=Figures label='Delete Figure' ");
	TwDefine("Menu/Figures opened=false");

	Menu_Cylinder();
	Menu_Prism();
	Menu_Projection();
};
void ATB::Menu_Cylinder()
{
	TwAddVarRW(bar, "Height", TW_TYPE_DOUBLE, &height_TW,
		" group=Cylinder value=0 min=0 max=1000 step=10 ");
	TwAddVarRW(bar, "Radius", TW_TYPE_DOUBLE, &radius_TW,
		" group=Cylinder value=0 min=0 max=1000 step=10 ");
	TwAddButton(bar, "Apply Cylinder", GetCallback_Cylinder, nullptr,
		" group=Cylinder ");
	TwAddSeparator(bar, nullptr, " group=Cylinder ");
	TwDefine(" Menu/Cylinder group=Figures ");
	TwDefine("Menu/Cylinder opened=false");
};
void ATB::Menu_Prism()
{
	TwAddVarRO(bar, "NumberPointsPrism", TW_TYPE_INT16, &number_points_TW,
		" group=Prism label=' Points on Base:' ");

	TwType my_points = TwDefineStruct("MyStruct_forPoints",
		Coordinates_TW, 3, sizeof(Position),
		nullptr, nullptr);
	TwAddVarRW(bar, " ", my_points, &temp_point,
		" group=Point ");
	TwAddButton(bar, "Push", Callback_Point, (void*)true,
		" group=Point ");
	TwAddButton(bar, "Pop", Callback_Point, (void*)false,
		" group=Point ");
	TwDefine(" Menu/Point group=Prism ");
	TwAddVarRW(bar, "Angle", my_points, &angle_TW,
		" group=Prism ");
	TwAddButton(bar, "Apply Prism", GetCallback_Prism, nullptr,
		" group=Prism ");
	TwAddSeparator(bar, nullptr, " group=Prism ");
	TwDefine(" Menu/Prism group=Figures ");

	TwDefine("Menu/Point opened=false");
	TwDefine("Menu/Prism opened=false");
};
void ATB::Menu_Projection()
{
	TwType my_choose_projection = TwDefineStruct("MyStruct_forProjection",
		Choose_projection, 3, sizeof(Projection::Pr_struct),
		nullptr, nullptr);
	TwAddVarRW(bar, "Projection", my_choose_projection, &Pr_type_TW,
		" group=Figures ");
	TwAddButton(bar, "Apply Projection", GetCallback_Pr, nullptr,
		" group=Projection ");
	TwAddButton(bar, "Delete last projection", Callback_Projection_Delete, nullptr,
		" group=Projection ");
	TwDefine("Menu/Projection opened=false");
};