##### Prelude #####
AC_INIT([rc-visual], [0.1.0], [danomatika@gmail.com])
AC_CONFIG_SRCDIR([src/rc-visual/main.cpp])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

##### Check for programs/libs #####
# check progs
AC_PROG_CXX
AC_PROG_RANLIB

# using c++ compiler and linker
AC_LANG_CPLUSPLUS

# check for headers
AC_HEADER_STDC
AC_CHECK_HEADER([SDL/SDL_gfxPrimitives.h],[],
	AC_MSG_ERROR([SDL_gfx headers not found]))

# check for libs
AC_CHECK_LIB(SDL_gfx, boxRGBA,
	AC_SUBST(SDL_GFX_LIBS, -lSDL_gfx),
	AC_MSG_ERROR([SDL_gfx library not found]))

# check for headers & libs
PKG_CHECK_MODULES(GLIB2, glib-2.0 >= 2.14,[],
	AC_MSG_ERROR([glib-2.0 library > 2.14 not found]))
PKG_CHECK_MODULES(SDL, sdl >= 1.2,[],
	AC_MSG_ERROR([SDL library >= 1.2 not found]))
#PKG_CHECK_MODULES(LIBLO, liblo >= 0.22,[],
#	AC_MSG_ERROR([liblo0 library >= 0.22 not found]))
AC_CHECK_LIB([lo], [lo_arg_pp],
	AC_SUBST([LIBLO_LIBS], ["-llo"]),
	AC_MSG_ERROR([liblo library not found]))

# arg to disable installation of config files, need to disable this for distcheck
#AC_ARG_ENABLE([config],
#  [AS_HELP_STRING([--disable-config],
#    [disable installation of config files])])
#AM_CONDITIONAL([ENABLE_CONFIG], [test "x$enable_config" != xno]) 

##### Output files #####
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/lib/Makefile
	src/rc-visual/Makefile
	src/rc-visual-send/Makefile
])
AC_OUTPUT

# Print a summary for the user
AC_MSG_RESULT([
	rc-visual $VERSION is now configured

	Source directory:     $srcdir
	Installation prefix:  $prefix
	C++ compiler:         $CXX $CXXFLAGS

])
