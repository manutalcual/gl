//
// Clase: wordl Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 13:43:45 2009

// Time-stamp: <2009-12-29 16:32:15 manuel>
//
//
// Includes
//
#include "world.hh"

DECLARE_LOG_VAR()

void ground::display ()
{
	nlogp (10, "Displaying ground.");
	static int called = 0;

	glColor3f(.5, .5, .5);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
}

building::building ()
{
	float zaxis = -2;

	glBegin (GL_QUADS);       /* cara frontal (roja) */
	glColor3f (1.0, 0.0, 0.0);
	glVertex3f (-1.0, -1.0, zaxis);
	glVertex3f (-1.0, 1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0, -1.0, zaxis);
	glEnd ();

	zaxis -= 2;

	glColor3f (0.0f, 1.0, 0.0);
	glBegin (GL_QUADS);       /* cara posterior (azul) */
	glVertex3f (-1.0, -1.0, zaxis);
	glVertex3f (-1.0, 1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0,  -1.0, zaxis);
	glEnd ();

	glColor3f (0.0, 0.0, 1.0);
	glBegin (GL_QUADS);       /* cara lateral der. */
	zaxis += 2.0;
	glVertex3f (1.0, -1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	zaxis -= 2;
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0, -1.0, zaxis);
	glEnd ();

#if 0
	glColor3f (0.0, 0.0, 1.0);
	glBegin (GL_QUADS);       /* cara lateral der. */
	zaxis += 2.0;
	glVertex3f (1.0, -1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	zaxis -= 2;
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0, -1.0, zaxis);
	glEnd ();
#endif

}





