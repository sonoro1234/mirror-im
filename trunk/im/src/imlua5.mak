PROJNAME = im
LIBNAME = imlua

OPT = YES

USE_LOH_SUBDIR = Yes
LOHDIR = lua5/loh
SRC = lua5/imlua.c lua5/imlua_aux.c lua5/imlua_convert.c lua5/imlua_file.c lua5/imlua_image.c lua5/imlua_palette.c lua5/imlua_util.c
DEF_FILE = lua5/imlua.def

SRCLUA = lua5/im_image.lua lua5/im_convert.lua
SRCLUADIR = lua5

INCLUDES = lua5

ifdef USE_LUA52
  LIBNAME := $(LIBNAME)52
else
  USE_LUA51 = Yes
  LIBNAME := $(LIBNAME)51
endif

USE_IM = YES
NO_LUALINK = Yes
IM = ..
