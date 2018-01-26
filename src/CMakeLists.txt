# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

if (WIN32 OR STATIC)
  add_definitions(-DSTATICLIB)
  # miniupnp changed their static define
  add_definitions(-DMINIUPNP_STATICLIB)
endif ()

# warnings are cleared only for GCC on Linux
if (NOT (MINGW OR APPLE OR FREEBSD OR OPENBSD OR DRAGONFLY))
  add_compile_options("${WARNINGS_AS_ERRORS_FLAG}") # applies only to targets that follow
endif()

function (bitlitas_private_headers group)
  source_group("${group}\\Private"
    FILES
      ${ARGN})
endfunction ()

function (bitlitas_install_headers subdir)
  install(
    FILES       ${ARGN}
    DESTINATION "include/${subdir}"
    COMPONENT   development)
endfunction ()

function (enable_stack_trace target)
  if(STACK_TRACE)
    set_property(TARGET ${target}
      APPEND PROPERTY COMPILE_DEFINITIONS "STACK_TRACE")
    if (STATIC)
      set_property(TARGET "${target}"
        APPEND PROPERTY LINK_FLAGS "-Wl,--wrap=__cxa_throw")
    endif()
  endif()
endfunction()

function (bitlitas_add_executable name)
  source_group("${name}"
    FILES
      ${ARGN})

  add_executable("${name}"
    ${ARGN})
  target_link_libraries("${name}"
    PRIVATE
      ${EXTRA_LIBRARIES})
  set_property(TARGET "${name}"
    PROPERTY
      FOLDER "prog")
  set_property(TARGET "${name}"
    PROPERTY
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  enable_stack_trace("${name}")
endfunction ()

function (bitlitas_add_library name)
    bitlitas_add_library_with_deps(NAME "${name}" SOURCES ${ARGN})
endfunction()

function (bitlitas_add_library_with_deps)
  cmake_parse_arguments(BITLITAS_ADD_LIBRARY "" "NAME" "DEPENDS;SOURCES" ${ARGN})
  source_group("${BITLITAS_ADD_LIBRARY_NAME}" FILES ${BITLITAS_ADD_LIBRARY_SOURCES})

  # Define a ("virtual") object library and an actual library that links those
  # objects together. The virtual libraries can be arbitrarily combined to link
  # any subset of objects into one library archive. This is used for releasing
  # libwallet, which combines multiple components.
  set(objlib obj_${BITLITAS_ADD_LIBRARY_NAME})
  add_library(${objlib} OBJECT ${BITLITAS_ADD_LIBRARY_SOURCES})
  add_library("${BITLITAS_ADD_LIBRARY_NAME}" $<TARGET_OBJECTS:${objlib}>)
  if (BITLITAS_ADD_LIBRARY_DEPENDS)
    add_dependencies(${objlib} ${BITLITAS_ADD_LIBRARY_DEPENDS})
  endif()
  set_property(TARGET "${BITLITAS_ADD_LIBRARY_NAME}" PROPERTY FOLDER "libs")
  target_compile_definitions(${objlib}
    PRIVATE $<TARGET_PROPERTY:${BITLITAS_ADD_LIBRARY_NAME},INTERFACE_COMPILE_DEFINITIONS>)
endfunction ()

include(Version)
bitlitas_add_library(version SOURCES ${CMAKE_BINARY_DIR}/version.cpp DEPENDS genversion)

add_subdirectory(common)
add_subdirectory(crypto)
add_subdirectory(ringct)
add_subdirectory(checkpoints)
add_subdirectory(cryptonote_basic)
add_subdirectory(cryptonote_core)
add_subdirectory(multisig)
if(NOT IOS)
  add_subdirectory(blockchain_db)
endif()
add_subdirectory(mnemonics)
if(NOT IOS)
  add_subdirectory(rpc)
  add_subdirectory(serialization)
endif()
add_subdirectory(wallet)
if(NOT IOS)
  add_subdirectory(p2p)
endif()
add_subdirectory(cryptonote_protocol)
if(NOT IOS)
  add_subdirectory(simplewallet)
  add_subdirectory(gen_multisig)
  add_subdirectory(daemonizer)
  add_subdirectory(daemon)
  add_subdirectory(blockchain_utilities)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_subdirectory(debug_utilities)
endif()

if(PER_BLOCK_CHECKPOINT)
  add_subdirectory(blocks)
endif()
