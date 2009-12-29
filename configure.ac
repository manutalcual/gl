AC_PREREQ([2.57])
AC_INIT([glearning],[0.0.1], [http://www.manusnook.net/], [glearning])
AM_INIT_AUTOMAKE([foreign dist-bzip2])
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_PROG_CXX

AC_CHECK_HEADERS([iostream stdio.h unistd.h string.h GL/gl.h GL/glut.h])

AC_CHECK_LIB([glut], [glutInit], [], AC_MSG_ERROR([prueba requires OpenGL Glut library.]))
AC_DEFINE(XGLUT, 1, [We have OpenGL Glut library])
GLUT_LIB="-lglut"

AC_CHECK_LIB([GL], [glEnable], [], AC_MSG_ERROR([prueba requires OpenGL library.]))
AC_DEFINE(XOPENGL, 1, [We have OpenGL library])
OPENGL_LIB="-lGL"

MACHINE=`uname -m`
AC_DEFINE_UNQUOTED(MACHINE, $MACHINE, [Architecture])

OS=`uname -s`
AC_DEFINE_UNQUOTED(OS, $OS, [Operating system])

AC_ARG_ENABLE([debug], AS_HELP_STRING([--enable-debug],
	     [Build with debug symbols and no optimizations (default: no)]),
	     [DEBUG=$enableval], [DEBUG=no])

if test x$DEBUG = xyes; then
       AC_DEFINE(DEBUG, 1, [Enable debugging code])
fi
AM_CONDITIONAL(DEBUG, [test "x$DEBUG" = xyes])

AC_ARG_WITH([log], AS_HELP_STRING([--with-log],
	     [Output verbose log. Useful only to debug. (default: no)]),
	     [LOG=$withval], [LOG=no])

if test x$LOG = xyes; then
       AC_DEFINE(LOG, 1, [Enable log])
fi
AM_CONDITIONAL(LOG, [test "x$LOG" = xyes])


AC_SUBST(OPENGL_LIB)
AC_SUBST(GLUT_LIB)
AC_SUBST(MACHINE)
AC_SUBST(OS)


AC_OUTPUT([Makefile src/Makefile])

