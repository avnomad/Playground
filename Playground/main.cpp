//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Playground.
 *
 *	Playground is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Playground is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Playground.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>

//#include <iostream>	// temp
//using std::cout;
//using std::cin;
//using std::endl;
//using std::cerr;
//using std::clog;
//using std::left;

#include <vector>
using std::vector;

#include <string>
#include <sstream>
#include <iomanip>

#include <algorithm>

#include <Space-Time/Vector2D.h>
typedef Vector2D<float> vec2;
typedef Vector2D<int> ivec2;
typedef unsigned int uint;
#include <Color/glColor.h>
using RGBA::Color;
#include <Color/namings/single precision colors.h>
#include <algorithms.h>



vec2 startingPosition;
vec2 currentPosition;
int focused = 0;
int beingDragged = 0;

#include "controls.h"

vector<Control *> controls;
vector<Box *> boxes;	// TODO replace vector with something that deletes its elements at destruction (and call of clear).
vector<Handle *> handles;
vector<Arrow *> arrows;

#include "display.h"
#include "handlers.h"

int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowSize(640,640);
	glutInitWindowPosition(620,160);
	glutCreateWindow("pathing");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,GL_REPLACE,GL_REPLACE);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// application initialization
	controls.push_back(new Control());

	boxes.push_back(new Box(vec2(300,200),vec2(340,225),orange));
	controls.push_back(boxes.back());
	boxes.push_back(new Box(vec2(400,400),vec2(440,430),yellow));
	controls.push_back(boxes.back());
	boxes.push_back(new Box(vec2(200,500),vec2(270,620),khaki));
	controls.push_back(boxes.back());
	boxes.push_back(new Box(vec2(320,150),vec2(440,158),brown));
	controls.push_back(boxes.back());
	boxes.push_back(new Box(vec2(590,320),vec2(630,400),violet));
	controls.push_back(boxes.back());

	handles.push_back(new Handle(vec2(100,450),red));
	controls.push_back(handles.back());
	handles.push_back(new Handle(vec2(400,100),lime));
	controls.push_back(handles.back());
	handles.push_back(new Handle(vec2(500,200),gold));
	controls.push_back(handles.back());
	handles.push_back(new Handle(vec2(550,200),ivory));
	controls.push_back(handles.back());

	arrows.push_back(new Arrow(vec2(50,550),vec2(0,15),azure));
	controls.push_back(arrows.back());

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passive);
	glutMotionFunc(active);
	glutMouseFunc(mouse);
	glutIdleFunc(always);
	glutMainLoop();
	return 0;
} // end function main
