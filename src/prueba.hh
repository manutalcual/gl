//
// Program: glearning Copyright (c) 2009 Sisdetec, S.L.U.
// Autor: Manuel Cano Muñoz
// Fecha: Tue Dec 29 13:43:45 2009
//
// Time-stamp: <2010-12-16 16:56:44 manuel>
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
#include <iostream>
#include <math.h>

#include "config.h"
#include "common.hh"
#include "world.hh"

//
// Suposedly default meaninful values.
//
#define INVALID -1
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

#define FOVY 45.0
#define ASPECT 1.0*width/height

#define NEAR 1
#define FAR 1000
#define ROTATION 0.0
#define AXIS 0.0
// camera orientation
#define ANGLE 0.0
#define DELTA_ANGLE 0.0
#define DELTA_MOVE 0.0
#define ACCEL 1
#define CAM_X 0.0     // camera's place
#define CAM_Y 1.25
#define CAM_Z 5.0
#define POINT_X 0.0   // point we look at
#define POINT_Y 0.0
#define POINT_Z -1.0f
#define CAMUP_X 0.0   // up vector
#define CAMUP_Y 1.0
#define CAMUP_Z 0.0
// end camera orientation
#define PERSPECTIVE 1
#define OPTSTO 100  // Options backstore stack max

//
// Windowing and drawing functions
//
void init ();
void clear ();
void reshape (int, int);
void display ();
void idle ();

void right_left (float ang);
void forward_backward (int i);

// Reset var to default values
void reset_vars ();

//
// Keyboard
//
void keyboard (unsigned char key, int x, int y);
void special_keyboard (int key, int x, int y);
void press_key (int key, int x, int y);
void release_key (int key, int x, int y);

//
// Mouse
//
void mouse (int button, int state, int x, int y);
void motion (int x, int y);

//
// Log functions
//
void init_log ();
void close_log ();
void show_vars ();

//
// Parameters functions
//
void parse_parameters (int argc, char ** argv);
char * get_opt_name (char * item);

//
// Boilerplate
//
void show_help (int argc, char ** argv);
void version ();

