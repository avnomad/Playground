void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	for(uint c = 0 ; c < controls.size() ; ++c)
	{
		glStencilFunc(GL_ALWAYS,c,0xffffffff);
		controls[c]->display();
	} // end for

	glutSwapBuffers();
} // end function display


