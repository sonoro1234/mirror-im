# Copyright (C) 2007-2012 LuaDist.
# Created by Peter Kapec
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.

project(im C CXX)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
#include ( cmake/dist.cmake )
macro ( install_library )
  foreach ( _file ${ARGN} )
    install ( TARGETS ${_file}
              RUNTIME DESTINATION ${LUAJIT_BIN}/immodules
              #LIBRARY DESTINATION ./lib 
              #ARCHIVE DESTINATION ./arch 
			  )
  endforeach()
endmacro ()
macro ( install_executable )
endmacro ()
macro ( install_header )
endmacro ()
#include ( lua )

# Find packages
	#find_package(Lua)
	find_package(OpenMP)
	#find_package(DirectShow)
	#find_package(ECW)

# platform tests for libtiff
	INCLUDE (TestBigEndian)
	TEST_BIG_ENDIAN(BIGENDIAN_PLATFORM)

	# todo - needs testing...
#~ 	IF(	BORLAND OR
#~ 		CMAKE_SYSTEM MATCHES "ow*" OR
#~ 		CMAKE_SYSTEM MATCHES "AIX*" OR
#~ 		CMAKE_SYSTEM MATCHES "SunOS*" OR
#~ 		CMAKE_SYSTEM MATCHES "HP-UX*"
#~ 		)
#~ 		ADD_DEFINITIONS(-DIM_DEFMATHFLOAT)
#~ 	ENDIF()

# inlcudes
	INCLUDE_DIRECTORIES (src include
		src/libtiff src/libjpeg src/libpng src/zlib src/libexif src/liblzf src/libjasper src/fftw src/minilzo)

# zlib lib
	FILE(GLOB SRCZLIB "src/zlib/*.c")

	SET_SOURCE_FILES_PROPERTIES(${SRCZLIB} PROPERTIES COMPILE_FLAGS "-fPIC")
	ADD_LIBRARY(z STATIC ${SRCZLIB})

# sources of external libs
	FILE(GLOB SRCTIFF "src/libtiff/*.c")
	IF(BIGENDIAN_PLATFORM)
		SET_SOURCE_FILES_PROPERTIES(${SRCTIFF} PROPERTIES COMPILE_FLAGS "-DWORDS_BIGENDIAN" )
	ENDIF()

	FILE(GLOB SRCLZO "src/minilzo/*.c")
	FILE(GLOB SRCJPEG "src/libjpeg/*.c")
	FILE(GLOB SRCPNG "src/libpng/*.c")
	FILE(GLOB SRCLZF "src/liblzf/*.c")
	FILE(GLOB_RECURSE SRCEXIF "src/libexif/*.c")

# im lib
	FILE(GLOB SRCC "src/*.c")
	FILE(GLOB SRCCPP "src/*.cpp")
	
	SET(SRC ${SRCC} ${SRCCPP} ${SRCLZO} ${SRCTIFF} ${SRCJPEG} ${SRCPNG} ${SRCLZF} ${SRCEXIF})
		#files not from im
		#MESSAGE(STATUS "removing " ${PROJECT_SOURCE_DIR}/src/im_capture_dx.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_capture_dx.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_format_ecw.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_format_wmv.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_sysfile_win32.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_sysfile_unix.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_dib.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_dibxbitmap.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/jas_binfile.c)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_format_jp2.cpp)
		list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/im_format_avi.cpp)
		#MESSAGE(STATUS ${SRC})
#SET_SOURCE_FILES_PROPERTIES(${SRC} PROPERTIES COMPILE_FLAGS "-DIM_PROCESS -DUSE_EXIF" )
	#SET_SOURCE_FILES_PROPERTIES(${SRC} PROPERTIES COMPILE_FLAGS "-DUSE_EXIF" )
	
	

	IF(WIN32)
		SET(SRC ${SRC} src/im_sysfile_win32.cpp src/im_dib.cpp src/im_dibxbitmap.cpp)
	ELSE()
		SET(SRC ${SRC} src/im_sysfile_unix.cpp)
	ENDIF()
	
	ADD_LIBRARY(im SHARED ${SRC}  src/im.rc src/im.def )
set_target_properties(im PROPERTIES COMPILE_FLAGS "-DUSE_EXIF")
	IF(MSYS OR MINGW OR CYGWIN)
		TARGET_LINK_LIBRARIES(im gdi32 comdlg32) # TODO GDI+ detection
	ENDIF ()

	ADD_DEPENDENCIES(im z)
	TARGET_LINK_LIBRARIES(im z)

# im_process lib
	FILE(GLOB SRC_IM_PROCESS "src/process/*.cpp")
	list(REMOVE_ITEM SRC_IM_PROCESS ${PROJECT_SOURCE_DIR}/src/process/im_fft.cpp)
 	SET(SRC_IM_PROCESS ${SRC_IM_PROCESS} src/im_convertbitmap.cpp src/im_convertcolor.cpp src/im_converttype.cpp) # copied into process folder - wtf???
	#SET_SOURCE_FILES_PROPERTIES(${SRC_IM_PROCESS} PROPERTIES COMPILE_FLAGS "-DIM_PROCESS" )

	ADD_LIBRARY(im_process SHARED ${SRC_IM_PROCESS} src/im_process.def)
set_target_properties(im_process PROPERTIES COMPILE_FLAGS "-DIM_PROCESS")
	IF(CYGWIN OR MSYS OR MINGW)
		TARGET_LINK_LIBRARIES(im_process im gdi32)
	ELSE ()
		TARGET_LINK_LIBRARIES(im_process im)
	ENDIF ()

	ADD_DEPENDENCIES(im_process im)

	IF(OPENMP_FOUND)
		ADD_LIBRARY(im_process_omp SHARED ${SRC_IM_PROCESS} src/im_process.def)

		# IMPORTANT !!! Do NOT set these flags on source files !!!!
		SET_TARGET_PROPERTIES(im_process_omp PROPERTIES
 			COMPILE_FLAGS "${OpenMP_C_FLAGS} ${OpenMP_CXX_FLAGS} -DIM_PROCESS"
			#COMPILE_FLAGS "${OpenMP_C_FLAGS} ${OpenMP_CXX_FLAGS}"
			LINK_FLAGS "${OpenMP_C_FLAGS} ${OpenMP_CXX_FLAGS}" )

		IF(CYGWIN OR MSYS OR MINGW)
			TARGET_LINK_LIBRARIES(im_process_omp im gdi32)
		ELSE ()
			TARGET_LINK_LIBRARIES(im_process_omp im)
		ENDIF ()

		ADD_DEPENDENCIES(im_process_omp im)

		install_library ( im_process_omp )
	ENDIF()

# im_jp2 lib
	FILE(GLOB_RECURSE SRCJP2 "src/libjasper/*.c")
	SET (SRC_IM_JP2  src/jas_binfile.c src/im_format_jp2.cpp ${SRCJP2})
	#MESSAGE(${SRCJP2})
	SET_SOURCE_FILES_PROPERTIES(${SRC_IM_JP2}  PROPERTIES
	COMPILE_DEFINITIONS  "EXCLUDE_JPG_SUPPORT;EXCLUDE_MIF_SUPPORT;EXCLUDE_PNM_SUPPORT;EXCLUDE_BMP_SUPPORT;EXCLUDE_PGX_SUPPORT;EXCLUDE_RAS_SUPPORT;EXCLUDE_TIFF_SUPPORT;JAS_GEO_OMIT_PRINTING_CODE;JAS_TYPES" )

	IF(CYGWIN OR MSYS OR MINGW)
#~ 		SET_SOURCE_FILES_PROPERTIES(${SRC_IM_JP2} PROPERTIES COMPILE_DEFINITIONS  "HAVE_UNISTD_H;HAVE_STDINT_H")
		SET_SOURCE_FILES_PROPERTIES(${SRC_IM_JP2}  PROPERTIES
	COMPILE_DEFINITIONS  "EXCLUDE_JPG_SUPPORT;EXCLUDE_MIF_SUPPORT;EXCLUDE_PNM_SUPPORT;EXCLUDE_BMP_SUPPORT;EXCLUDE_PGX_SUPPORT;EXCLUDE_RAS_SUPPORT;EXCLUDE_TIFF_SUPPORT;JAS_GEO_OMIT_PRINTING_CODE;JAS_TYPES:HAVE_UNISTD_H;HAVE_STDINT_H" )
	ENDIF()

	ADD_LIBRARY(im_jp2 SHARED ${SRC_IM_JP2} src/im_jp2.def)
	TARGET_LINK_LIBRARIES (im_jp2 im)

	ADD_DEPENDENCIES(im_jp2 im)

# im_fftw
	FILE(GLOB SRC_IM_FFTW "src/fftw/*.c")
	SET(SRC_IM_FFTW ${SRC_IM_FFTW} src/process/im_fft.cpp)

 	#SET_SOURCE_FILES_PROPERTIES(${SRC_IM_FFTW} PROPERTIES COMPILE_FLAGS "-DFFTW_ENABLE_FLOAT -DIM_PROCESS" )
#	SET_SOURCE_FILES_PROPERTIES(${SRC_IM_FFTW} PROPERTIES COMPILE_FLAGS "-DFFTW_ENABLE_FLOAT" )

	ADD_LIBRARY(im_fftw SHARED ${SRC_IM_FFTW} src/im_fftw.def)
	set_target_properties(im_fftw PROPERTIES COMPILE_FLAGS "-DFFTW_ENABLE_FLOAT")# -DIM_PROCESS")
	TARGET_LINK_LIBRARIES (im_fftw im_process im)

	ADD_DEPENDENCIES(im_fftw im_process im)

############################################################################################

# im_capture lib
	# Direct X with Direct Show (or Windows SDK) detection
	# needs "dshow.h" and "strmiids.lib" (which is available in MinGW) -> NOT WORKING !

	IF(WIN32 AND NOT MINGW)
		message(STATUS "WIN32 AND NOT MINGW")
#~ 		FIND_PATH(DXTRANS_INCLUDE_DIR dxtrans.h)
#~ 		FIND_LIBRARY( STRMIIDS_LIBRARY NAMES strmiids)

#~ 		MESSAGE("DXTRANS_INCLUDE_DIR:"${DXTRANS_INCLUDE_DIR})
#~ 		MESSAGE("STRMIIDS_LIBRARY:"${STRMIIDS_LIBRARY})

#~ 		IF(DXTRANS_INCLUDE_DIR AND STRMIIDS_LIBRARY)
		IF( DIRECTSHOW_FOUND )
			INCLUDE_DIRECTORIES(${DIRECTSHOW_INCLUDE_DIRS})

			ADD_LIBRARY(im_capture SHARED src/im_capture_dx.cpp resources/im_capture.def)
#~ 			TARGET_LINK_LIBRARIES (im_capture im ${STRMIIDS_LIBRARY})
			TARGET_LINK_LIBRARIES (im_wmv im ${DIRECTSHOW_LIBRARIES})

			ADD_DEPENDENCIES(im_capture im)

			install_library ( im_capture )
		ENDIF()
	ENDIF()

# im_wmv lib
	IF(WIN32 AND NOT MINGW)
		# Windows Media SDK detection - need "wmsdk.h" and "wmvcore.lib"
		FIND_PATH(WMSDK_INCLUDE_DIR wmsdk.h)
		FIND_LIBRARY( WMVCORE_LIBRARY NAMES wmvcore)

		MESSAGE("WMSDK_INCLUDE_DIR:" ${WMSDK_INCLUDE_DIR})
		MESSAGE("WMVCORE_LIBRARY:" ${WMVCORE_LIBRARY})

		IF( WMSDK_INCLUDE_DIR AND WMVCORE_LIBRARY )
			INCLUDE_DIRECTORIES(${WMSDK_INCLUDE_DIR})

			SET_SOURCE_FILES_PROPERTIES(src/im_format_wmv.cpp
				PROPERTIES COMPILE_FLAGS "-D_CRT_NON_CONFORMING_SWPRINTFS" )

			ADD_LIBRARY(im_wmv SHARED src/im_format_wmv.cpp src/im_wmv.def)
			TARGET_LINK_LIBRARIES (im_wmv im ${WMVCORE_LIBRARY})

			ADD_DEPENDENCIES(im_wmv im)

			install_library ( im_wmv )
		ENDIF()
	ENDIF()

# im_avi lib
	IF(WIN32 AND NOT MINGW)
		FIND_LIBRARY( VFW32_LIBRARY NAMES vfw32 vfw_ms32 vfw_avi32)
		MESSAGE("VFW32_LIBRARY:" ${VFW32_LIBRARY})

		IF(VFW32_LIBRARY)
			ADD_LIBRARY(im_avi SHARED src/im_format_avi.cpp src/im_avi.def)
			TARGET_LINK_LIBRARIES (im_avi im ${VFW32_LIBRARY})

			ADD_DEPENDENCIES(im_avi im)

			install_library ( im_avi )
		ENDIF()
	ENDIF()

# im_ecw  lib
	# ECW JPEG 2000 SDK - need "NCSECWClient.h" and "ncsecw.lib"
#~ 	FIND_PATH(NCSECWCLIENT_INCLUDE_DIR NCSECWClient.h)
#~ 	FIND_LIBRARY(NCSECW_LIBRARY NAMES NCSEcw ncsecw)

#~ 	MESSAGE("NCSECWCLIENT_INCLUDE_DIR:"${NCSECWCLIENT_INCLUDE_DIR})
#~ 	MESSAGE("NCSECW_LIBRARY:"${NCSECW_LIBRARY})

	IF( ECW_FOUND )
		INCLUDE_DIRECTORIES ( ${NCSECWCLIENT_INCLUDE_DIR} )

		ADD_LIBRARY(im_ecw SHARED src/im_format_ecw.cpp src/im_ecw.def)
		TARGET_LINK_LIBRARIES (im_ecw im ${NCSECW_LIBRARY})

		ADD_DEPENDENCIES(im_ecw im)

		install_library ( im_ecw )
	ENDIF()

############################################################################################

if(LUA_FOUND)

	include_directories(${LUA_INCLUDE_DIR} src/lua5/libimlua src/lua5/libimlua/lh)

# use *.lh files
	add_definitions(-DIMLUA_USELH)

# imlua lib
	FILE(GLOB_RECURSE SRC_IMLUALIB "src/lua5/libimlua/*.c")
#~ 	SET_SOURCE_FILES_PROPERTIES( ${SRC_IMLUALIB} PROPERTIES COMPILE_FLAGS "-DIM_PROCESS -DIMLUA_USELH" )
	ADD_LIBRARY(imlua SHARED ${SRC_IMLUALIB})
	TARGET_LINK_LIBRARIES(imlua ${LUA_LIBRARIES} im)
	install_library( imlua )

# imlua module
	install_lua_module ( imlua_module src/lua5/imlua/imlua_module.c resources/imlua.def LINK  imlua )
	set_target_properties ( imlua_module PROPERTIES OUTPUT_NAME imlua )

# imlua_process5
#~ 	set ( SRC_IMLUA_PROCESS src/lua5/modules/imlua_process.c src/lua5/modules/imlua_kernel.c )
	FILE(GLOB SRC_IMLUA_PROCESS "src/lua5/modules/process/*.c")

	SET_SOURCE_FILES_PROPERTIES( ${SRC_IMLUA_PROCESS} PROPERTIES COMPILE_FLAGS "-DIM_PROCESS" )
	install_lua_module ( imlua_process ${SRC_IMLUA_PROCESS} LINK imlua im_process  )

# imlua_process5_omp
	if(OPENMP_FOUND)
		# IMPORTANT !!! Do NOT set these flags on source files !!!!
		install_lua_module(imlua_process_omp  ${SRC_IMLUA_PROCESS} LINK imlua im_process_omp)
		set_target_properties(imlua_process_omp PROPERTIES
				COMPILE_FLAGS "${OpenMP_C_FLAGS} ${OpenMP_CXX_FLAGS} -DIM_PROCESS"
#~ 				COMPILE_FLAGS "${OpenMP_C_FLAGS} ${OpenMP_CXX_FLAGS} "
				LINK_FLAGS "${OpenMP_C_FLAGS} ${OpenMP_CXX_FLAGS}" )

#		install(TARGETS imlua_process_omp DESTINATION ${INSTALL_CMOD} )
	endif()

# imlua_fftw5
	install_lua_module ( imlua_fftw src/lua5/modules/imlua_fftw.c resources/imlua_fftw.def LINK  imlua  im_fftw )

# imlua_jp2
	install_lua_module ( imlua_jp2 src/lua5/modules/imlua_jp2.c resources/imlua_jp2.def LINK imlua im_jp2 )

# imlua_avi
	if (TARGET im_avi )
	  install_lua_module ( imlua_avi src/lua5/modules/imlua_avi.c resources/imlua_avi.def LINK imlua im_avi} )
	endif ( )

# imlua_capture
	if (TARGET im_capture )
	    install_lua_module ( imlua_capture src/lua5/modules/imlua_capture.c resources/imlua_capture.def  LINK imlua im_capture )
	endif ( )

# imlua_wmv
	if (TARGET im_wmv )
	  install_lua_module ( imlua_wmv src/lua5/modules/imlua_wmv.c resources/imlua_wmv.def LINK  imlua im_wmv )
	endif ( )

endif()

############################################################################################


# install all libs
install_library ( im im_process im_jp2 im_fftw )
install(FILES imffi.lua DESTINATION ${LUAJIT_BIN}/lua)
# install headers
#install_header ( include/ )
# install other
#install_data ( COPYRIGHT README )
# install documentation
#install_doc ( doc/ )