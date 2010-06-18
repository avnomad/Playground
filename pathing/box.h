struct Box : public FocusAwareControl
{
	vec2 lowerLeft;
	vec2 upperRight;
	Color<float> color;
	static vec2 startingLowerLeft;
	static vec2 startingUpperRight;


	Box(vec2 lowerLeftCorner, vec2 upperRightCorner, Color<float> rectangleColor)
		:lowerLeft(lowerLeftCorner),upperRight(upperRightCorner),color(rectangleColor)
	{												// TODO should check parameters' relationship
		hasFocus = false;
	} // end Box constructor


	virtual void display()
	{
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT | GL_LINE_BIT);
			glPolygonMode(GL_FRONT,GL_FILL);
			glColor(color);
			glRectf(lowerLeft.x,lowerLeft.y,upperRight.x,upperRight.y);
			glPolygonMode(GL_FRONT,GL_LINE);
			glColor(0.5*gray);
			if(hasFocus)
			{
				glLineWidth(3);
				glRectf(lowerLeft.x,lowerLeft.y,upperRight.x,upperRight.y);
				glColor(yellow);
			} // end if
			glLineWidth(1);
			glRectf(lowerLeft.x,lowerLeft.y,upperRight.x,upperRight.y);
		glPopAttrib();
	} // end function display


	virtual void pickUp()
	{
		startingLowerLeft = lowerLeft;
		startingUpperRight = upperRight;
	} // end function pickUp


	virtual void drag()
	{
		vec2 displacement = currentPosition-startingPosition;
		lowerLeft = startingLowerLeft + displacement;
		upperRight = startingUpperRight + displacement;
	} // end function drag


	virtual void drop()
	{
		vec2 displacement = currentPosition-startingPosition;
		lowerLeft = startingLowerLeft + displacement;
		upperRight = startingUpperRight + displacement;
	} // end function drop
}; // end struct Box

vec2 Box::startingLowerLeft;
vec2 Box::startingUpperRight;