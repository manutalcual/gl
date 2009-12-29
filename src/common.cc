//
// Clase: common Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 15:58:38 2009
//
// Time-stamp: <2009-12-29 19:00:47 manuel>
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







