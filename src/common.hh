//
// Clase: common Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 15:58:38 2009
//
// Time-stamp: <2011-11-06 10:51:10 manuel>
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
#include <iostream>
#include "config.h"


#ifndef __common_h__
#define __common_h__

#ifdef OS
#define MKOS(s) mkos(s)
#define mkos(s) #s
#else
#define MKOS(s) ""
#endif

#ifdef MACHINE
#define MKMACHINE(s) mkmachine(s)
#define mkmachine(s) #s
#endif


#define DECLARE_LOG_VAR() extern long log_priority;	\
	extern long log_spaces;


#define SET_LOG_PRIORITY(x) log_priority = x;
#define SET_LOG_SPACES(x) log_spaces = x;
#define CREATE_LOG_FILE(x) _logFiles[x] = std::ofstream (x, ios::out);

#define nelog(x)
#define nelogf(x, y)
#define nlogp(x, y)
#define nlogf(x)
#define nlogfr(x, y)

#ifdef LOG
#define msg(x) std::cerr << "[" << __FILE__ \
	<< ":" << __LINE__ << "]: " << x		\
	<< std::endl;

#define elog(x) std::cerr << "["				\
	<< __FILE__ << ":"							\
	<< __LINE__ << "]: " << x << std::endl;

#define elogn(x) std::cerr << x;
	
#define elogf(x, y) logFiles[y] << "["			\
	<< __FILE__ << ":"							\
	<< __LINE__ << "]: " << x << "\n";
	
#define logp(pri, x) {do {						\
			if(pri >= log_priority) {			\
				elog(spc(log_spaces) << x);		\
			}									\
		} while (0);}

#define logpn(pri, x) {do {						\
			if(pri >= log_priority) {			\
				elogn(spc(log_spaces) << x);	\
			}									\
		} while (0);}
	
#define logf(x) {do {							\
			if(10 >= log_priority) {			\
				elog(spc(log_spaces) << x);		\
			}									\
		} while (0);}
	
#define logfr(pri, x) {do {						\
			if(pri >= log_priority) {			\
				elog(spc(log_spaces) << x);		\
			}									\
		} while (0);} 
#else
#define msg(x)
#define elog(x)
#define elogn(x)
#define elogf(x, y)
#define logp(pri, x)
#define logpn(pri, x)
#define logf(x)
#define logfr(pri, x)
#endif

#define TRAP(cond, msg) { if(cond) { elog(msg); throw msg; } }

const char * spc (int x);


#endif // __common_h__


