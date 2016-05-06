@echo off
REM This builds all the libraries of the folder for 1 uname  

call tecmake %1 %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_process" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_process" "USE_OPENMP=Yes" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_jp2" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_avi" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_fftw" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_lzo" %2 %3 %4 %5 %6 %7 %8
  
REM Building for the default (USE_LUA51) 
REM or for the defined at the environment

call tecmake %1 "MF=imlua5" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_process5" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_process5" "USE_OPENMP=Yes" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_jp25" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_avi5" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_fftw5" %2 %3 %4 %5 %6 %7 %8

REM call tecmake %1 "MF=imlua5" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_process5" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_process5" "USE_OPENMP=Yes" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_jp25" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_avi5" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_fftw5" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8

REM call tecmake %1 "MF=imlua5" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_process5" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_process5" "USE_OPENMP=Yes" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_jp25" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_avi5" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_fftw5" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8

REM call tecmake %1 "MF=imlua5" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_process5" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_process5" "USE_OPENMP=Yes" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_jp25" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_avi5" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_fftw5" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8

REM WMV and Capture are NOT available in some compilers,
REM so this may result in errors, just ignore them.
call tecmake %1 "MF=im_wmv" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_wmv5" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_wmv5" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_wmv5" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_wmv5" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=im_capture" %2 %3 %4 %5 %6 %7 %8
call tecmake %1 "MF=imlua_capture5" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_capture5" "USE_LUA51=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_capture5" "USE_LUA52=Yes" %2 %3 %4 %5 %6 %7 %8
REM call tecmake %1 "MF=imlua_capture5" "USE_LUA53=Yes" %2 %3 %4 %5 %6 %7 %8
