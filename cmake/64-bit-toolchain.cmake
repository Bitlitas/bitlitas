# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set (CMAKE_SYSTEM_NAME Windows)

set (GCC_PREFIX x86_64-w64-mingw32)
set (CMAKE_C_COMPILER ${GCC_PREFIX}-gcc)
set (CMAKE_CXX_COMPILER ${GCC_PREFIX}-g++)
set (CMAKE_AR ar CACHE FILEPATH "" FORCE)
set (CMAKE_NM nm CACHE FILEPATH "" FORCE)
set (CMAKE_LINKER ld CACHE FILEPATH "" FORCE)
#set (CMAKE_RANLIB ${GCC_PREFIX}-gcc-ranlib CACHE FILEPATH "" FORCE)
set (CMAKE_RC_COMPILER windres)

set (CMAKE_FIND_ROOT_PATH "${MSYS2_FOLDER}/mingw64")

# Ensure cmake doesn't find things in the wrong places
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER) # Find programs on host
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY) # Find libs in target
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) # Find includes in target

set (MINGW_FLAG "-m64")
set (USE_LTO_DEFAULT false)
