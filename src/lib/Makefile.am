# visual lib of classes

# the library to build, dont install just link to execs
noinst_LIBRARIES = libvisual.a

# libs sources, headers here because we dont want to install them
libvisual_a_SOURCES =	Sprite.h Sprite.cpp \
						Sprite_Group.h Sprite_Group.cpp \
						Sprite_Collection.h Sprite_Collection.cpp \
						Sprite_File.h Sprite_File.cpp \
						Osc_Server.h Osc_Server.cpp

# include paths
AM_CPPFLAGS = $(CXXFLAGS) $(GLIB2_CFLAGS) $(SDL_CFLAGS) $(SDL_GFX_CFLAGS) $(LIBLO_CFLAGS)

# libs to link
AM_LDFLAGS = $(GLIB2_LIBS) $(SDL_LIBS) $(SDL_GFX_LIBS) $(LIBLO_LIBS)

