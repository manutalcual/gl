//
// Clase: common Copyright (c) 2009 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 15:58:38 2009

// Time-stamp: <2009-12-29 16:15:51 manuel>
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
#define msg(x) std::cerr << "[" << __FILE__ << ":" <<					\
														 __LINE__ << "]: " << x << std::endl;
					
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


