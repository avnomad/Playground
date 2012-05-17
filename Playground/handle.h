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