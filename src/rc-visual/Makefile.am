# rc-visual

# load externals variables
include $(top_srcdir)/externals/externals.mk

# programs to build
bin_PROGRAMS = rc-visual

# bin sources, headers here because we dont want to install them
rc_visual_SOURCES = \
        Common.h Config.h Config.cpp \
        App.h App.cpp \
        main.cpp \
        Scene.h Scene.cpp \
        SceneManager.h SceneManager.cpp \
		ResourceManager.h ResourceManager.cpp \
		Util.h Util.cpp \
        objects/Bitmap.h \
        objects/Bitmap.cpp \
        objects/DrawableObject.h \
        objects/Line.h \
        objects/Objects.h \
        objects/Pixel.h \
        objects/Rect.h \
        objects/Sprite.h \
        objects/Sprite.cpp \
        objects/Image.h \
        objects/Image.cpp \
        objects/Text.h

# include c++ flags
rc_visual_CXXFLAGS = $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS) \
			-I$(top_srcdir)/src

# local libs to link
rc_visual_LDADD = $(EXTERNALS_LIBS)

# libs to link
rc_visual_LDFLAGS = $(SDL_LIBS) $(LO_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS) \
                        $(SDL_TTF_LIBS) $(SDL_image_LIBS)

