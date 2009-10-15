
# program to build
bin_PROGRAMS = rc-visual

# program's sources
rc_visual_SOURCES = main.cpp

# local libraries needed to build
rc_visual_LDADD = ../lib/libvisual.a

# include paths
rc_visual_CPPFLAGS = $(CXXFLAGS) -I../lib $(GLIB2_CFLAGS) $(SDL_CFLAGS) $(SDL_GFX_CFLAGS) $(LIBLO_CFLAGS)

# libs to link
rc_visual_LDFLAGS = $(GLIB2_LIBS) $(SDL_LIBS) $(SDL_GFX_LIBS) $(LIBLO_LIBS)

