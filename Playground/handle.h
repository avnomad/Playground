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

struct Handle : public FocusAwareControl
{
	vec2 position;
	Color<float> color;
	static vec2 startingPosition;


	Handle(vec2 handlePosition, Color<float> handleColor)
		:position(handlePosition),color(handleColor)
	{
		hasFocus = false;
	} // end Handle constructor


	virtual void display()
	{
		glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT);
			glDisable(GL_POINT_SMOOTH);
			if(hasFocus)
			{
				glColor(0.5*gray);
				glPointSize(9);
				glBegin(GL_POINTS);
					glVertex2fv(position);
				glEnd();
				glColor(yellow);
				glPointSize(7);
				glBegin(GL_POINTS);
					glVertex2fv(position);
				glEnd();
				glColor(0.5*gray);
				glPointSize(5);
				glBegin(GL_POINTS);
					glVertex2fv(position);
				glEnd();
				glColor(color);
				glPointSize(3);
				glBegin(GL_POINTS);
					glVertex2fv(position);
				glEnd();
			}
			else
			{
				glColor(0.5*gray);
				glPointSize(7);
				glBegin(GL_POINTS);
					glVertex2fv(position);
				glEnd();
				glColor(color);
				glPointSize(5);
				glBegin(GL_POINTS);
					glVertex2fv(position);
				glEnd();
			} // end else
		glPopAttrib();
	} // end function display


	virtual void pickUp()
	{
		this->startingPosition = position;
	} // end function pickUp


	virtual void drag()
	{
		vec2 displacement = currentPosition-::startingPosition;
		position = this->startingPosition + displacement;
	} // end function drag


	virtual void drop()
	{
		vec2 displacement = currentPosition-::startingPosition;
		position = this->startingPosition + displacement;
	} // end function drop
}; // end struct Handle

vec2 Handle::startingPosition;