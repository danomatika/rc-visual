# C++ Static Library Makefile autogenerated by premake
# Don't edit this file! Instead edit `premake.lua` then rerun `make`

ifndef CONFIG
  CONFIG=Debug
endif

# if multiple archs are defined turn off automated dependency generation
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := ../bin
  LIBDIR := ../lib
  OBJDIR := ../obj/visualClasses/Debug
  OUTDIR := ../lib
  CPPFLAGS := $(DEPFLAGS) -D "LINUX" -D "DEBUG" -D "_DEBUG" -I "../src" -I "../src/classes" -I "/usr/include" -I "../externals" -I "../externals/visualframework/src" -I "../externals/visualframework/externals" -I "../externals/visualframework/externals/include"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -Wall -Wno-unknown-pragmas -ggdb
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"../lib" -L"../externals/lib" -L"../externals/visualframework/externals/lib" -L"/usr/lib" -lSDL -lSDL_gfx -ltinyxmlD -loscpackD -lvisualframeworkD
  LDDEPS :=
  RESFLAGS := -D "LINUX" -D "DEBUG" -D "_DEBUG" -I "../src" -I "../src/classes" -I "/usr/include" -I "../externals" -I "../externals/visualframework/src" -I "../externals/visualframework/externals" -I "../externals/visualframework/externals/include"
  TARGET := libvisualClassesD.a
 BLDCMD = ar -rcs $(OUTDIR)/$(TARGET) $(OBJECTS) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := ../bin
  LIBDIR := ../lib
  OBJDIR := ../obj/visualClasses/Release
  OUTDIR := ../lib
  CPPFLAGS := $(DEPFLAGS) -D "LINUX" -D "NDEBUG" -I "../src" -I "../src/classes" -I "/usr/include" -I "../externals" -I "../externals/visualframework/src" -I "../externals/visualframework/externals" -I "../externals/visualframework/externals/include"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O2 -Wall -Wno-unknown-pragmas
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -s -L"../lib" -L"../externals/lib" -L"../externals/visualframework/externals/lib" -L"/usr/lib" -lSDL -lSDL_gfx -ltinyxml -loscpack -lvisualframework
  LDDEPS :=
  RESFLAGS := -D "LINUX" -D "NDEBUG" -I "../src" -I "../src/classes" -I "/usr/include" -I "../externals" -I "../externals/visualframework/src" -I "../externals/visualframework/externals" -I "../externals/visualframework/externals/include"
  TARGET := libvisualClasses.a
 BLDCMD = ar -rcs $(OUTDIR)/$(TARGET) $(OBJECTS) $(TARGET_ARCH)
endif

OBJECTS := \
	$(OBJDIR)/Osc_Server.o \
	$(OBJDIR)/BitmapSprite.o \
	$(OBJDIR)/Sprite_Group.o \
	$(OBJDIR)/Sprite_Collection.o \
	$(OBJDIR)/Sprite.o \
	$(OBJDIR)/Sprite_File.o \

MKDIR_TYPE := msdos
CMD := $(subst \,\\,$(ComSpec)$(COMSPEC))
ifeq (,$(CMD))
  MKDIR_TYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  MKDIR_TYPE := posix
endif
ifeq ($(MKDIR_TYPE),posix)
  CMD_MKBINDIR := mkdir -p $(BINDIR)
  CMD_MKLIBDIR := mkdir -p $(LIBDIR)
  CMD_MKOUTDIR := mkdir -p $(OUTDIR)
  CMD_MKOBJDIR := mkdir -p $(OBJDIR)
else
  CMD_MKBINDIR := $(CMD) /c if not exist $(subst /,\\,$(BINDIR)) mkdir $(subst /,\\,$(BINDIR))
  CMD_MKLIBDIR := $(CMD) /c if not exist $(subst /,\\,$(LIBDIR)) mkdir $(subst /,\\,$(LIBDIR))
  CMD_MKOUTDIR := $(CMD) /c if not exist $(subst /,\\,$(OUTDIR)) mkdir $(subst /,\\,$(OUTDIR))
  CMD_MKOBJDIR := $(CMD) /c if not exist $(subst /,\\,$(OBJDIR)) mkdir $(subst /,\\,$(OBJDIR))
endif

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking visualClasses
	-@$(CMD_MKBINDIR)
	-@$(CMD_MKLIBDIR)
	-@$(CMD_MKOUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning visualClasses
ifeq ($(MKDIR_TYPE),posix)
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)
else
	-@if exist $(subst /,\,$(OUTDIR)/$(TARGET)) del /q $(subst /,\,$(OUTDIR)/$(TARGET))
	-@if exist $(subst /,\,$(OBJDIR)) del /q $(subst /,\,$(OBJDIR))
	-@if exist $(subst /,\,$(OBJDIR)) rmdir /s /q $(subst /,\,$(OBJDIR))
endif

$(OBJDIR)/Osc_Server.o: ../src/classes/Osc_Server.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BitmapSprite.o: ../src/classes/BitmapSprite.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Sprite_Group.o: ../src/classes/Sprite_Group.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Sprite_Collection.o: ../src/classes/Sprite_Collection.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Sprite.o: ../src/classes/Sprite.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Sprite_File.o: ../src/classes/Sprite_File.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)

