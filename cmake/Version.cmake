# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

function (write_static_version_header hash)
  set(VERSIONTAG "${hash}")
  configure_file("src/version.cpp.in" "version.cpp")
endfunction ()

find_package(Git QUIET)
if ("$Format:$" STREQUAL "")
  # We're in a tarball; use hard-coded variables.
  write_static_version_header("release")
elseif (GIT_FOUND OR Git_FOUND)
  message(STATUS "Found Git: ${GIT_EXECUTABLE}")
  add_custom_target(genversion ALL
    COMMAND           "${CMAKE_COMMAND}"
                      "-D" "GIT=${GIT_EXECUTABLE}"
                      "-D" "TO=${CMAKE_BINARY_DIR}/version.cpp"
                      "-P" "cmake/GenVersion.cmake"
    BYPRODUCTS        "${CMAKE_BINARY_DIR}/version.cpp"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
else()
  message(STATUS "WARNING: Git was not found!")
  write_static_version_header("unknown")
endif ()
