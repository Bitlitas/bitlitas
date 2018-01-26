# Copyright (c) 2018, Bitlitas
# All rights reserved.

# We aren't even going to check the system for an installed LMDB driver, as it is too
# critical a consensus component to rely on dynamically linked libraries
message(STATUS "Using ${ARCH_WIDTH}-bit LMDB from source tree")
add_subdirectory(liblmdb)
set(LMDB_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/liblmdb" CACHE STRING "LMDB Include path")
set(LMDB_LIBRARY "lmdb" CACHE STRING "LMDB Library name")
