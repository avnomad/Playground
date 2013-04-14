//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

void passive(int x, int y)
{
	int id;
	y = glutGet(GLUT_WINDOW_HEIGHT)-1-y;
	glReadPixels(x,y,1,1,GL_STENCIL_INDEX,GL_INT,&id);
	if(id != focused)
	{
		controls[focused]->looseFocus();
		controls[focused=id]->getFocus();
	} // end if
} // end function passive


void active(int x, int y)
{
	y = glutGet(GLUT_WINDOW_HEIGHT)-1-y;
	currentPosition = vec2(x,y);
	controls[beingDragged]->drag();			
} // end function active


void mouse(int button, int state, int x, int y)
{
	int id;

	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			y = glutGet(GLUT_WINDOW_HEIGHT)-1-y;
			glReadPixels(x,y,1,1,GL_STENCIL_INDEX,GL_INT,&id);
			if(id)
			{
				std::rotate(controls.begin()+id,controls.begin()+(id+1),controls.end());
				beingDragged = controls.size()-1;
				if(focused == id)
					focused = beingDragged;
				else if(focused > id && focused < controls.size())
					focused--;
			}
			else
				beingDragged = 0;
			startingPosition = vec2(x,y);
			controls[beingDragged]->pickUp();
		} // end if
		if(state == GLUT_UP)
		{
			y = glutGet(GLUT_WINDOW_HEIGHT)-1-y;
			currentPosition = vec2(x,y);
			controls[beingDragged]->drop();
		} // end if
	} // end if
} // end function mouse


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
} // end function reshape


void always()
{
	glutPostRedisplay();
} // end function always