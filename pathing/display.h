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

	glColor(blue);
	glBegin(GL_LINES);
		glVertex2fv(handles[0]->position);
		glVertex2fv(handles[1]->position);
	glEnd();

	glutSwapBuffers();
} // end function display


