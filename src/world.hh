//
// Clase: wordl Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 13:43:45 2009
//
// Time-stamp: <2011-11-05 21:11:32 manuel>
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
// Includes
//
#include <GL/gl.h>
#include <GL/glut.h>

#include "common.hh"

#ifndef __wordl_h__
#define __wordl_h__

template <class T>
class list_t
{
public:
	list_t ()
		: _list (glGenLists(1))
		{
			glNewList (_list, GL_COMPILE);

			_object = new T;

			glEndList ();
		}
	~list_t ()
		{
			delete _object;
		}
	GLuint list () { return _list; }
private:
	GLuint _list;
	T * _object;
};

class ground
{
public:
	static void display ();
private:
};

class building
{
public:
	building ();
private:
};

#endif // __wordl_h__
