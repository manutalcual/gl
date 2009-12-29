//
// Clase: wordl Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 13:43:45 2009
//
// Time-stamp: <2009-12-29 19:05:15 manuel>
//
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
//   02110-1301	USA
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

//
// Three walls room
//
building::building ()
{
	float zaxis = -2;

	glBegin (GL_QUADS);       // front wall
	glColor3f (1.0, 0.0, 0.0);
	glVertex3f (-1.0, -1.0, zaxis);
	glVertex3f (-1.0, 1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0, -1.0, zaxis);
	glEnd ();

	zaxis -= 2;

	glColor3f (0.0f, 1.0, 0.0);
	glBegin (GL_QUADS);       // back wall
	glVertex3f (-1.0, -1.0, zaxis);
	glVertex3f (-1.0, 1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0,  -1.0, zaxis);
	glEnd ();

	glColor3f (0.0, 0.0, 1.0);
	glBegin (GL_QUADS);       // right wall
	zaxis += 2.0;
	glVertex3f (1.0, -1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	zaxis -= 2;
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0, -1.0, zaxis);
	glEnd ();

#if 0
	glColor3f (0.0, 0.0, 1.0);
	glBegin (GL_QUADS);       // left wall
	zaxis += 2.0;
	glVertex3f (1.0, -1.0, zaxis);
	glVertex3f (1.0, 1.0, zaxis);
	zaxis -= 2;
	glVertex3f (1.0, 1.0, zaxis);
	glVertex3f (1.0, -1.0, zaxis);
	glEnd ();
#endif

}





