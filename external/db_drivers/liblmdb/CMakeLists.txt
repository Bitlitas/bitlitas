# Copyright (c) 2018, Bitlitas
# All rights reserved.

if(FREEBSD)
  add_definitions(-DMDB_DSYNC=O_SYNC)
endif()

if(ANDROID)
  add_definitions("-DANDROID=1")
endif()


set (lmdb_sources
mdb.c
midl.c)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(lmdb
  ${lmdb_sources})
target_link_libraries(lmdb
  PRIVATE
    ${CMAKE_THREAD_LIBS_INIT})
if(WIN32)
  target_link_libraries(lmdb
    -lntdll)
endif()
if(${ARCH_WIDTH} EQUAL 32)
  target_compile_definitions(lmdb
    PUBLIC -DMDB_VL32)
endif()
set_property(TARGET lmdb APPEND PROPERTY COMPILE_FLAGS "-fPIC")
