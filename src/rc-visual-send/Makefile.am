# rc-visual-send

# load externals variables
include $(top_srcdir)/externals/externals.mk

# programs to build
bin_PROGRAMS = rc-visual-send

# bin sources, headers here because we dont want to install them
rc_visual_send_SOURCES = main.cpp

# include paths
rc_visual_send_CPPFLAGS = $(CXXFLAGS) $(EXTERNALS_CFLAGS) -I$(top_srcdir)/src

# local libs to link
rc_visual_send_LDADD = $(EXTERNALS_LIBS)

# libs to link
rc_visual_send_LDFLAGS = $(LO_LIBS)

