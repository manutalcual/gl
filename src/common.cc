//
// Clase: common Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 15:58:38 2009

// Time-stamp: <2009-12-29 16:15:51 manuel>
//
//
// Includes
//
#include "common.hh"


long log_priority = 5;
long log_spaces = 0;


const char * spc (int x)
{
	static char str[1024];
	int i = 0;

	for (i = 0; i < x; ++i)
		str[i] = ' ';

	str[i] = '\0';

	return str;
}







