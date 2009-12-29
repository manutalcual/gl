//
//
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "prueba.hh"

DECLARE_LOG_VAR();

FILE * fd = NULL; // log 

//
//Mouse button states (presed or not)
///
int rbutton_state = 0;
int lbutton_state = 0;
int button_x_mot = 0;
int button_y_mot = 0;

float width = WINDOW_WIDTH;
float height = WINDOW_HEIGHT;
int perspective = 1; // 0, glFrustum; 1 gluPerspective 

int op = 1; // 0 = sum, 1 = rest 

float angle = ANGLE;
float delta_angle = DELTA_ANGLE;
int delta_move = DELTA_MOVE;

//
//Rotation. Yep, just try them.
//
//
int axis = AXIS; // current used axes (bitfield: 0x1, 0x2, 0x3, etc.) 
float rot_x = ROTATION;
float rot_y = ROTATION;
float rot_z = ROTATION;
float axes[] = {0., 0., 0.}; // Ax1s to turn over 

//
//To keep trace of program parameters.
//
//
struct option {
	int len;
	char * full_name;
	char short_name;
	float val;
};

//
//Enums for program parameters.
//
//TAKE CARE of maintaining in the same order as the opts[] parameters
//structure (below)
//
//
enum eopts { 
	e_fovy, e_aspect, // for gluPerspective 
	e_near, e_far, // for glPerspective and glFrustum 

	// almost not used 
	e_rotation,
	e_axis_x, e_axis_y, e_axis_z,
	e_perspective,

	// these nine for gluLookAt 
	e_cam_x, e_cam_y, e_cam_z,
	e_point_x, e_point_y, e_point_z,
	e_camup_x, e_camup_y, e_camup_z,
	
	// next, nothing to do with GL, just program boilerplate 
	e_version, e_help, e_end
};
//
//The program parameters themselves
//
//
struct option opts[] = {
	{ 4, "fovy", 'f', FOVY },
	{ 6, "aspect", 'a', ASPECT },
	{ 4, "near", 'n', NEAR },
	{ 3, "far", 'r', FAR },
	{ 8, "rotation", 't', ROTATION },

	// these 'axis' parameters are not intended to be used, but here
	//are them if you want to try them 
	{ 6, "axis-x", '\0', AXIS },
	{ 6, "axis-y", '\0', AXIS },
	{ 6, "axis-z", '\0', AXIS },

	// don't set this as you can change it at runtime 
	{ 11, "perspective", 'p', PERSPECTIVE },

	{ 5, "cam-x", '\0', CAM_X },
	{ 5, "cam-y", '\0', CAM_Y },
	{ 5, "cam-z", '\0', CAM_Z },

	{ 7, "point-x", '\0', POINT_X },
	{ 7, "point-y", '\0', POINT_Y },
	{ 7, "point-z", '\0', POINT_Z },

	{ 7, "camup-x", '\0', CAMUP_X },
	{ 7, "camup-y", '\0', CAMUP_Y },
	{ 7, "camup-z", '\0', CAMUP_Z },

	{ 7, "version", 'v', 0 },
	{ 4, "help", 'h', 0 }
};

//
//This is a naïve parameter stack for unused parameters.
//Beware, this is a security hole, so don't use it
//in production software.
//
//
char * optsto[OPTSTO];
int optsto_stack = -1; // first entry is at zero but 
                       //I increment it _before_
                       //using it.
                        
enum { e_x, e_z };
int move[] = {0, 0};

//
// C++ magic!
//
list_t<building> * lst_build = NULL;

//
//Yep! Main program.
//
//
int main (int argc, char ** argv)
{
	reset_vars ();
	init_log ();
	parse_parameters (argc, argv);

	glutInit (&argc, argv);

	glutInitDisplayMode (GLUT_DOUBLE |
						 GLUT_DEPTH | 
						 GLUT_RGBA);

	glutInitWindowPosition (100, 100);
	glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow (argv[0]);

	init ();

	glutIgnoreKeyRepeat (GLUT_KEY_REPEAT_OFF);

	glutKeyboardFunc (keyboard);
	glutSpecialFunc (press_key);
	glutSpecialUpFunc (release_key);

	glutMouseFunc (mouse);
	glutMotionFunc (motion);

	glutDisplayFunc (display);
	glutIdleFunc (display);

	glutReshapeFunc (reshape);

	glutMainLoop ();

	glutIgnoreKeyRepeat (GLUT_KEY_REPEAT_DEFAULT);

	delete lst_build;
	close_log ();

	return 0;
}

void init ()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH /* GL_FLAT */);
	glEnable (GL_DEPTH_TEST);
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;

	lst_build = new list_t<building>;
}

void clear ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void idle ()
{
	//
	//This is a huge resource eater.
	//There _must_ be a better way of doing this.
	//
	//
	display ();
}

void display ()
{
	clear ();

	if (delta_move) {
		forward_backward (delta_move);
	}

	if (delta_angle) {
		angle += delta_angle;
		right_left (angle);
	}

	ground::display ();

	nlogp (10, "Calling list.: " << lst_build->list());
	glCallList (lst_build->list());

	glutSwapBuffers ();
}

void reshape (int x, int y)
{
	logp (10, "Reshaping with "
		  << x << ", " << y << ", " << opts[e_fovy].val);

	//
	// Prevent divide by zero
	//
	if (width == 0)
		width = 1;

	width = x;
	height = y;
	float ratio = 1.0 * width / height;


	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	glViewport (0, 0, width, height);

	gluPerspective (opts[e_fovy].val,
					ratio,
					opts[e_near].val, 
					opts[e_far].val);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (
		// camera position 
		opts[e_cam_x].val,
		opts[e_cam_y].val,
		opts[e_cam_z].val,
		// point to look at 
		opts[e_point_x].val,
		opts[e_point_y].val,
		opts[e_point_z].val,
		// up vector 
		opts[e_camup_x].val,
		opts[e_camup_y].val,
		opts[e_camup_z].val);

	show_vars ();
}

void right_left (float ang)
{
	logp (10, "Angle: " << ang << ", " << angle);
	logp (10, "Z axis: " << opts[e_point_z].val);
	opts[e_point_x].val = sin(ang);
	opts[e_point_z].val = -cos(ang);
	logp (10, "Z axis: " << opts[e_point_z].val);

	glLoadIdentity ();
	gluLookAt (opts[e_cam_x].val,
			   opts[e_cam_y].val,
			   opts[e_cam_z].val, 
			   opts[e_cam_x].val + opts[e_point_x].val,
			   opts[e_cam_y].val + opts[e_point_y].val,
			   opts[e_cam_z].val + opts[e_point_z].val,
			   0.0f, 1.0f, 0.0f);

	logp (10, "Z axis: " << opts[e_point_z].val);
	show_vars ();
}

void forward_backward (int i)
{
	opts[e_cam_x].val += i * (opts[e_point_x].val) * 0.05;
	opts[e_cam_z].val += i * (opts[e_point_z].val) * 0.05;

	glLoadIdentity ();
	gluLookAt (opts[e_cam_x].val,
			   opts[e_cam_y].val,
			   opts[e_cam_z].val, 
			   opts[e_cam_x].val + opts[e_point_x].val,
			   opts[e_cam_y].val + opts[e_point_y].val,
			   opts[e_cam_z].val + opts[e_point_z].val,
			   0.0f, 1.0f, 0.0f);
	show_vars ();
}

void press_key(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT:
			delta_angle = -0.005f;
			break;
		case GLUT_KEY_RIGHT:
			delta_angle = 0.005f;
			break;
		case GLUT_KEY_UP:
			delta_move = 1;
			break;
		case GLUT_KEY_DOWN:
			delta_move = -1;
			break;
	}
}

void release_key (int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT: 
		case GLUT_KEY_RIGHT:
			delta_angle = 0.0f;
			break;
		case GLUT_KEY_UP: 
		case GLUT_KEY_DOWN:
			delta_move = 0;
			break;
	}
}


void special_keyboard (int key, int x, int y)
{
	switch (key) {

	case GLUT_KEY_LEFT:
		logp (10, "Moving angle: " << angle);
		angle -= 0.01;
		logp (10, "\tx: " << opts[e_point_x].val);
		logp (10, "\ty: " << opts[e_point_y].val);
		logp (10, "\tafter move, angle: " << angle);
		right_left (angle);
		logp (10, "moved: ");
		logp (10, "\tx: " << opts[e_point_x].val);
		logp (10, "\ty: " << opts[e_point_y].val);
		break;
	case GLUT_KEY_RIGHT:
		logp (10, "Moving angle: " << angle);
		angle += 0.01;
		logp (10, "\tx: " << opts[e_point_x].val);
		logp (10, "\ty: " << opts[e_point_y].val);
		right_left (angle);
		logp (10, "\tafter move, angle: " << angle);
		logp (10, "moved: ");
		logp (10, "\tx: " << opts[e_point_x].val);
		logp (10, "\ty: " << opts[e_point_y].val);
		break;
	case GLUT_KEY_UP:
		logp (10, "Moving back and forth:");
		logp (10, "\tx: " << opts[e_cam_x].val);
		logp (10, "\ty: " << opts[e_cam_y].val);
		forward_backward (1);
		logp (10, "\tmoved x: " << opts[e_cam_x].val);
		logp (10, "\tmoved y: " << opts[e_cam_y].val);
		break;
	case GLUT_KEY_DOWN:
		logp (10, "Moving back and forth:");
		logp (10, "\tx: " << opts[e_cam_x].val);
		logp (10, "\ty: " << opts[e_cam_y].val);
		forward_backward (-1);
		logp (10, "\tmoved x: " << opts[e_cam_x].val);
		logp (10, "\tmoved y: " << opts[e_cam_y].val);
		break;
	default:
		;
	}
}

void keyboard (unsigned char key, int x, int y)
{
	int mod = 0;

	switch(key) {
	case 'v':
		mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT) {
			show_vars ();
		} else {
			logp (10, "Rotation: " << axis);
			logp (10, "Axis y:   " << (axis & 0x1));
			logp (10, "Axis x:   " << (axis & 0x2));
			logp (10, "Axis z:   " << (axis & 0x4));
		}
		break;
	case '1':
		axis ^= 0x1;
		break;
	case '2':
		axis ^= 0x2;
		break;
	case '3':
		axis ^= 0x4;
		break;
	case '.':
		//rotate ();
		reshape (width, height);
		break;
	case '-':
		op = 1;
		break;
	case '+':
		op = 0;
		break;
	case 'x':
		++axis;
		if (axis == 3)
			axis = 0;
		break;
	case 'G':
		opts[e_rotation].val += (op ? -0.5f : 0.5f);
		//logp (10, "rotate: " << rotation);
		break;
	case 'g':
		//rotate ();
		//logp (10, "rotate: " << rotation);
		reshape (width, height);
		break;
	case 'f':
		opts[e_fovy].val += (op ? -0.5f : 0.5f);
		//logp (10, "fovy: " << );
		reshape (width, height);
		break;
	case 'a':
		opts[e_aspect].val += (op ? -0.5f : 0.5f);
		reshape (width, height);
		//logp (10, "aspect: " << aspect);
		break;
	case 'n':
		opts[e_near].val += (op ? -0.5f : 0.5f);
		reshape (width, height);
		//logp (10, "near: " << near);
		break;
	case 'r':
		opts[e_far].val += (op ? -0.5f : 0.5f);
		reshape (width, height);
		//logp (10, "far: " << far);
		break;
	case 'p':
	case 'P':
		opts[e_perspective].val = 1;
	reshape (width, height);
	//logp (10, "perspective.");
	break;
	case 'o':
	case 'O':
		opts[e_perspective].val = 0;
	reshape (width, height);
	//logp (10, "ortho.");
	break;
	case 'z':
		reset_vars ();
		reshape (width, height);
		break;
	case 'q':
		opts[e_fovy].val += 0.5f;
		//logp (10, "fovy: " << fovy);
		reshape (width, height);
		break;
	case 'w':
		opts[e_fovy].val -= 0.5f;
		//logp (10, "fovy: " << fovy);
		reshape (width, height);
		break;
	case 27:   // escape 
		exit (0);
		break;
	default:
		logp (10, "Key " << key << " pulsed.");
		break;
	}
}

void mouse (int button, int state, int x, int y)
{
	logp (10, "Button: " << button << ", state " << state
		  << ", x " << x << ", y " << y);

	switch (button) {
	case 3:
		opts[e_fovy].val += 0.2f;
		nlogp (10, "fovy: " << fovy);
		reshape (width, height);
		break;
	case 4:
		opts[e_fovy].val -= 0.2f;
		nlogp (10, "fovy: " << fovy);
		reshape (width, height);
		break;
	default:
		if (button == GLUT_RIGHT_BUTTON) {
			if (state == GLUT_DOWN) {
				button_y_mot = y;
				rbutton_state = GLUT_DOWN;
			} else {
				rbutton_state = GLUT_UP;
			}
		} else if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				button_x_mot = x;
				button_y_mot = y;
				lbutton_state = GLUT_DOWN;
			} else {
				lbutton_state = GLUT_UP;
			}
		}
		break;
	}
	show_vars ();
}

void motion (int x, int y)
{
	if (lbutton_state == GLUT_DOWN) {
		logp (10, "Mouse motion: " << x << ", "
			  << y << ": " << button_x_mot);
		
		
		if (x > button_x_mot) {
			opts[e_cam_x].val += 0.01;
			logp (10, "moving x axis: " << opts[e_cam_x].val);
			right_left (opts[e_cam_x].val);
		} else if (x < button_x_mot) {
			move[e_x] -= 0.01;
			logp (10, "moving x axis: " << opts[e_cam_x].val);
			right_left (opts[e_cam_x].val);
		}

		if (y > button_y_mot) {
			//move[e_z] += 1;
			forward_backward (1);
		} else if (y < button_y_mot) {
			//move[e_z] -= 1;
			forward_backward (-1);
		}

		if (axis & 0x2) {
			if (x > button_x_mot) {
				//
				//this was used to rotate the cube, but when I was
				//learning to use OpenGL, so it is not a good
				//example (it simply rotates de cube way too fast!)
				///
				opts[e_axis_y].val -= 1; //(x - button_x_mot);
				button_x_mot = x;

			} else if (x < button_x_mot) {
				opts[e_axis_y].val += 1; //(button_x_mot - x);
				button_x_mot = x;

				move[e_x] -= 0.01;
				right_left (move[e_x]);
			}
		}
		if (axis & 0x1) {
			if (y > button_y_mot) {
				opts[e_axis_x].val -= 1; //(y - button_y_mot);
				button_y_mot = y;
			} else if (y < button_y_mot) {
				opts[e_axis_x].val += 1; //(button_y_mot - y);
				button_y_mot = y;
			}
		}

		logp (10, "Rotate by vals:");
		logp (10, "\tx " << opts[e_axis_x].val);
		logp (10, "\ty " << opts[e_axis_y].val);
		logp (10, "\tz " << opts[e_axis_z].val);

		//
		//Unfortunately, we have not a third axis on the mouse:(
		//

		if (axis & 0x4) {
			if (y > button_y_mot) {
				opts[e_axis_z].val -= (y - button_y_mot);
				button_y_mot = y;
			} else if (y < button_y_mot) {
				opts[e_axis_z].val += (button_y_mot - y);
				button_y_mot = y;
			}}

		nlogp (10, "Displaying things?");
	} else if (rbutton_state == GLUT_DOWN) {
	}
}

void reset_vars ()
{
	logp (10, "Zeroing vars.\n");
	opts[e_fovy].val = FOVY;
	opts[e_aspect].val = ASPECT;
	opts[e_near].val = NEAR;
	opts[e_far].val = FAR;
	opts[e_perspective].val = PERSPECTIVE;

	opts[e_cam_x].val = CAM_X;
	opts[e_cam_y].val = CAM_Y;
	opts[e_cam_z].val = CAM_Z;
	opts[e_point_x].val = POINT_X;
	opts[e_point_y].val = POINT_Y;
	opts[e_point_z].val = POINT_Z;
	opts[e_camup_x].val = CAMUP_X;
	opts[e_camup_y].val = CAMUP_Y;
	opts[e_camup_z].val = CAMUP_Z;

	opts[e_rotation].val = ROTATION;
	opts[e_axis_x].val = AXIS;
	opts[e_axis_y].val = AXIS;
	opts[e_axis_z].val = AXIS;
	axis = 0;
}

void show_vars ()
{
	logp (10, "----------------------------------------------");
	logp (10, "Fovy:   " << opts[e_fovy].val << " (" << opts[e_fovy].full_name << ")");
	logp (10, "Aspect: " << opts[e_aspect].val << " (" << opts[e_aspect].full_name << ")");
	logp (10, "Near:   " << opts[e_near].val << " (" << opts[e_near].full_name << ")");
	logp (10, "Far:    " << opts[e_far].val << " (" << opts[e_far].full_name << ")");
	logp (10, "");
	logp (10, "Camera settings:");
	logp (10, "Angle: " << angle);
	logp (10, "Cam x: " << opts[e_cam_x].val);
	logp (10, "Cam y: " << opts[e_cam_y].val);
	logp (10, "Cam z: " << opts[e_cam_z].val);
	logp (10, "Pos x: " << opts[e_point_x].val);
	logp (10, "Pos y: " << opts[e_point_y].val);
	logp (10, "Pos z: " << opts[e_point_z].val);
	logp (10, "Cam up x: " << opts[e_camup_x].val);
	logp (10, "Cam up y: " << opts[e_camup_y].val);
	logp (10, "Cam up z: " << opts[e_camup_z].val);
	logp (10, "");

	logp (10, "Axis x:   " << (axis & 0x1));
	logp (10, "Axis y:   " << (axis & 0x2));
	logp (10, "Axis z:   " << (axis & 0x4));
	logp (10, "----------------------------------------------");
}

void parse_parameters (int argc, char ** argv)
{
	int i = 0;

	logp (10, "Parsing parameters. (argc=" << argc << ", elems=" << e_end << ")");
	for (i = 1; i < argc; ++i) {
		int elem = 0;
		int beg = 1;
		logp (10, "Option: " << argv[i]);

		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0') {
			logp (10, "Stop processing options.");
			return;
		}

		if (argv[i][0] != '-' && optsto_stack < OPTSTO) {
			optsto[++optsto_stack] = argv[i];
			logp (10, "\tvalue "
				  << optsto[optsto_stack]
				  << ", saved at "
				  << optsto_stack);
			continue;
		}

		if (argv[i][1] == '-')
			beg = 2;

		char * p = get_opt_name(argv[i]);
		int len = 0;

		if (p) {
			len = p - argv[i];
			logp (10, "\tEqual at "
				  << (int)*p
				  << " ("
				  << *p
				  << ", "
				  << len
				  << ")");
			argv[i][p - argv[i]] = '\0';
			logp (10, "\t\tstripped option: "
				  << argv[i]);
		} else {
			logp (10, "\tNo equal, " << argv[i]);
			len = strlen(argv[i]);
		}

		for (; elem < e_end; ++elem) {
            logp (10, "\t\t\t\telem: " << opts[elem].full_name << "; (" 
				  << elem << ")");

			if (! p)
				len = opts[elem].len;
						
			if ((strncmp(opts[elem].full_name, &argv[i][beg], len) == 0)
				|| (opts[elem].short_name == argv[i][1]))
			{
				logp (10, "\t\tok, "
					  << &argv[i][beg]
					  << " found.");

				if (strcmp(opts[elem].full_name, "help") == 0)
					show_help (argc, argv);
					
				if (strcmp(opts[elem].full_name, "version") == 0)
					version ();

				if (p) {
					opts[elem].val = atof(p + 1);
				} else {
					logp (10, "\t\tthere is no value asociated.");
					if (optsto_stack > INVALID) {
						logp (10, "\t\t\tpicking option from stack.");
						//optsto[optsto_stack - 1]);
						opts[elem].val = atof(optsto[optsto_stack--]);
					} else {
						if (argv[++i][0] == '-') {
							logp (10, "\t\t\tnext option is not a value, skipping.");
							--i;
							continue;
						}
						logp (10, "\t\t\tok, picking next option: "
							  << argv[i]);
						opts[elem].val = atof(argv[i]);
					}
				}
				logp (10, "\t\tvalue of "
					  << opts[elem].full_name
					  << ": "
					  << opts[elem].val);
				break;
			} else {
				logp (10, "\t\t'"
					  << opts[elem].full_name
					  << "' is not '"
					  << &argv[i][beg]
					  << "'");
			}
		}
	}

	//reset_vars ();
}

char * get_opt_name (char * item)
{
	char * p = item;

	while (*p) {
		if (*p == '=')
			return p;
		++p;
	}

	return NULL;
}

void init_log ()
{
	fd = fopen("log", "wb");
	if (! fd)
		exit (1);

	logp (10, "Application begun.");
}

void close_log ()
{
	fclose (fd);
}

void show_help (int argc, char ** argv)
{
	std::cout << argv[0] << " [options]" << std::endl;
	std::cout << std::endl;

	exit (0);
}

void version ()
{
	std::cout << PACKAGE_NAME " version " PACKAGE_VERSION
		" (" MKOS(OS) "-" MKMACHINE(MACHINE) ")" << std::endl;
	std::cout << "Copyright (C) 2009 Sisdetec, S.L.U." << std::endl;
	std::cout << "License GPLv3+: GNU GPL version 3 or later "
		"<http://gnu.org/licenses/gpl.html>" << std::endl;
	std::cout << "This is free software; you are free "
		"to change and redistribute it.\n"
		"There is NO WARRANTY, to the extent permitted by law." << std::endl;

	exit (0);
}

