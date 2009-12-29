//
// Clase: wordl Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 13:43:45 2009

// Time-stamp: <2009-12-29 16:27:56 manuel>
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


