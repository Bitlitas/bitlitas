# Copyright (c) 2018, Bitlitas
# All rights reserved.

cmake_minimum_required(VERSION 2.8.7)

project(easylogging CXX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Threads)

add_library(easylogging
  easylogging++.cc)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(easylogging
  PRIVATE
    ${CMAKE_THREAD_LIBS_INIT})

# GUI/libwallet install target
if (BUILD_GUI_DEPS)
    if(IOS)
        set(lib_folder lib-${ARCH})
    else()
        set(lib_folder lib)
    endif()
    install(TARGETS easylogging
        ARCHIVE DESTINATION ${lib_folder}
        LIBRARY DESTINATION ${lib_folder})
endif()
set_property(TARGET easylogging APPEND PROPERTY COMPILE_FLAGS "-fPIC")

