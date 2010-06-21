vector<vec2> calculateConnector(vec2 e1, vec2 e2, vec2 direction)
{
	vector<vec2> vertices;
	vec2 diff = 0.5*(e2-e1);
	vec2 x = diff.projection(direction);
	vec2 y = diff-x;

	vertices.push_back(e1);
	if(x.norm() > y.norm())	// the direction of inequality can be passed as a template parameter
	{
		vertices.push_back(e1+y);
		vertices.push_back(e2-y);
	}
	else
	{
		vertices.push_back(e1+x);
		vertices.push_back(e2-x);
	} // end else
	vertices.push_back(e2);

	return vertices;
} // end function calculateConnector


const float PI = 3.141592654;
const float minArrowLength = 14;
const float arrowHeadSide = 8;
const float arrowHeadAngle = 25.0*(PI/180.0);	// 25 degrees
const float annotationHeight = 12;
const float annotationHeightAboveBaseline = 8;	// should replace with exact value when I get my hands on a GLUT documentation.


inline bool shouldRotateText(float angle)	// angle is expected to be in [-ð,ð] and measured in rads.
{
	return angle > 3*PI/4 || angle < -PI/4;
} // end function rotateText

						// TODO deal with the case v1 == v2.
vec2 displayMeasurementArrows(vec2 v1, vec2 v2, float b, float textLength)
{
	vec2 origin;
	float measurement = (v2-v1).norm();
	vec2 x = (v2-v1)/measurement;
	vec2 y = x.perpendicular();
	vec2 u = arrowHeadSide*cos(arrowHeadAngle)*x;
	vec2 v = arrowHeadSide*sin(arrowHeadAngle)*y;
	float arrowLength = (measurement-textLength)/2;
	bool mirrorOrigin = shouldRotateText((v2-v1).angle());

	v2 += b*y;
	v1 += b*y;

	if(arrowLength >= minArrowLength)
	{
		glBegin(GL_LINES);
			glVertex2fv(v1);
			glVertex2fv(v1+arrowLength*x);
			glVertex2fv(v2-arrowLength*x);
			glVertex2fv(v2);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2fv(v2-u-v);
			glVertex2fv(v2);
			glVertex2fv(v2-u+v);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2fv(v1+u+v);
			glVertex2fv(v1);
			glVertex2fv(v1+u-v);
		glEnd();
		
		if(!mirrorOrigin)
			origin = v1+arrowLength*x-v;
		else
			origin = v2-arrowLength*x+v;
	}
	else
	{
		glBegin(GL_LINES);
			glVertex2fv(v1-minArrowLength*x);
			glVertex2fv(v1);
			glVertex2fv(v2);
			glVertex2fv(v2+minArrowLength*x);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2fv(v2+u+v);
			glVertex2fv(v2);
			glVertex2fv(v2+u-v);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2fv(v1-u-v);
			glVertex2fv(v1);
			glVertex2fv(v1-u+v);
		glEnd();
		if(!mirrorOrigin)
			if(textLength <= measurement)
				origin = v1+arrowLength*x-v;
			else
				origin = v2+u+v;
		else
			if(textLength <= measurement)
				origin = v2-arrowLength*x+v;
			else
				origin = v1-u+v+annotationHeightAboveBaseline*y;
	} // end else	

	return origin;
} // end function displayMeasurementArrows

										// TODO should rearange contents of displayMeasurementArrows
										// and displayMeasurement. avoid duplications.
const int significantDigits = 4;
const float leftMargin = 1;
const float rightMargin = 1;
const float verticalHeight = annotationHeight;

void displayMeasurement(vec2 v1, vec2 v2, float b)
{
	float measurement = (v2-v1).norm();	// duplicate from displayMeasurementArrows
	vec2 x = (v2-v1)/measurement;	// >>
	vec2 y = x.perpendicular();	// >>
	std::ostringstream converter;
	std::string annotation;
	float angle;

	glPushAttrib(GL_LINE_BIT);
		glLineWidth(1.0);
		converter << std::setprecision(significantDigits) << measurement << 'p';
		annotation = converter.str();
		float textLength = (annotationHeight/152.38)*stringLenght(annotation.begin(),annotation.end());
		vec2 origin = displayMeasurementArrows(v1,v2,b,leftMargin+textLength+rightMargin);
		if(shouldRotateText(angle = (v2-v1).angle()))
			angle -= PI;
		displayString(origin,annotationHeight,1,angle*(180.0/PI),annotation.begin(),annotation.end());
		glLineWidth(0.5);
		glBegin(GL_LINES);
			glVertex2fv(v1+verticalHeight/2*y+b*y);
			glVertex2fv(v1-verticalHeight/2*y+b*y);
			glVertex2fv(v2+verticalHeight/2*y+b*y);
			glVertex2fv(v2-verticalHeight/2*y+b*y);
		glEnd();
	glPopAttrib();
} // end function displayMeasurement


void boxMeasurements(const Box &box)
{
	displayMeasurement(box.lowerLeft,vec2(box.lowerLeft.x,box.upperRight.y),6);
	displayMeasurement(vec2(box.lowerLeft.x,box.upperRight.y),box.upperRight,6);
	displayMeasurement(box.upperRight,vec2(box.upperRight.x,box.lowerLeft.y),6);
	displayMeasurement(vec2(box.upperRight.x,box.lowerLeft.y),box.lowerLeft,6);
} // end function boxMeasurements


void display()
{
	glStencilMask(0xffffffff);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	for(uint c = 0 ; c < controls.size() ; ++c)
	{
		glStencilFunc(GL_ALWAYS,c,0xffffffff);
		controls[c]->display();
	} // end for
	glStencilMask(0);

	vector<vec2> vertices = calculateConnector(handles[0]->position,handles[1]->position,arrows[0]->direction());

	// render connector
	glColor(blue);
	glBegin(GL_LINE_STRIP);
		for(uint c = 0 ; c < vertices.size() ; ++c)
			glVertex2fv(vertices[c]);
	glEnd();
	vertices.clear();	// clear connector

	glColor(lime);
	displayMeasurement(handles[2]->position,handles[3]->position,6);
	glColor(green);
	boxMeasurements(*boxes[1]);
	boxMeasurements(*boxes[3]);

	glutSwapBuffers();
} // end function display