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

	glutSwapBuffers();
} // end function display


