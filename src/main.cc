/*
 *
 */
#include <unistd.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glut.h>

int main(int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA);
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (10, 10);
	glutCreateWindow (argv[0]);

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();

	glutMainLoop ();

	return 0;
}

