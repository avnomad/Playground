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

struct Arrow : public FocusAwareControl
{
	static const float sqrt3; // the square root of 3
	vec2 head;
	vec2 tail;
	Color<float> color;
	static float a; // triangle side length
	static vec2 startingHead;
	static vec2 startingTail;
	static bool headSelected;

	Arrow(vec2 arrowTail, vec2 direction, Color<float> arrowColor)
		:head(arrowTail+direction),tail(arrowTail),color(arrowColor)
	{
		hasFocus = false;
	} // end Handle constructor


	inline vec2 direction()
	{
		return head - tail;
	} // end function direction


	virtual void display()
	{
		glPushAttrib(GL_LINE_BIT | GL_POLYGON_BIT | GL_POINT_BIT | GL_CURRENT_BIT);
			glDisable(GL_POINT_SMOOTH);
			glPolygonMode(GL_FRONT,GL_FILL);
			if(hasFocus)
			{
				a = 18.5;
				glLineWidth(5);
				glPointSize(8);
				glColor(0.5*gray);
				draw();

				a = 16;
				glLineWidth(3);
				glPointSize(6);
				glColor(yellow);
				draw();

				a = 13.5;
				glLineWidth(1);
				glPointSize(4);
				glColor(0.5*gray);
				draw();

				a = 11;
				glLineWidth(1);
				glPointSize(2);
				glColor(color);
				draw();
			}
			else
			{
				a = 15.5;
				glLineWidth(3);
				glPointSize(6);
				glColor(0.5*gray);
				draw();

				a = 13;
				glLineWidth(1);
				glPointSize(4);
				glColor(color);
				draw();
			} // end else
		glPopAttrib();
	} // end function display


	inline void draw()
	{
		glBegin(GL_LINES);
			glVertex2fv(tail);
			glVertex2fv(head);
		glEnd();
		glBegin(GL_TRIANGLES);
			vec2 d = direction();
			if(d == vec2(0,0))
				d = vec2(0,1);
			d = d/d.norm();
			vec2 y = d*(a/sqrt3);
			vec2 x = d.perpendicular()*(a*0.5);
			glVertex2fv(head+y);
			glVertex2fv(head-0.5*y+x);
			glVertex2fv(head-0.5*y-x);
		glEnd();
		glBegin(GL_POINTS);
			glVertex2fv(tail);
		glEnd();
	} // end function draw


	virtual void pickUp()
	{
		if((startingPosition-tail).normInf() > 3 && (startingPosition-head).norm() <= (15/sqrt3))
		{
			headSelected = true;
		}
		else
		{
			headSelected = false;
			startingTail = tail;
		} // end else
		startingHead = head;
	} // end function pickUp


	virtual void drag()
	{
		vec2 displacement = currentPosition-startingPosition;
		if(!headSelected)
			tail = startingTail + displacement;
		head = startingHead + displacement;
	} // end function drag


	virtual void drop()
	{
		vec2 displacement = currentPosition-startingPosition;
		if(!headSelected)
			tail = startingTail + displacement;
		head = startingHead + displacement;
	} // end function drop
}; // end struct Arrow

const float Arrow::sqrt3 = 1.732050808; // the square root of 3
float Arrow::a; // triangle side length
vec2 Arrow::startingHead;
vec2 Arrow::startingTail;
bool Arrow::headSelected;