# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

cmake_minimum_required(VERSION 2.8.7)

unset(ENV{CC})
unset(ENV{CXX})

project(translations)

add_executable(generate_translations_header generate_translations_header.c)

find_program(LRELEASE lrelease)
if(LRELEASE STREQUAL "LRELEASE-NOTFOUND")
  set(ts_files "")
  message(WARNING "lrelease program not found, translation files not built")
else()
  execute_process(COMMAND ${LRELEASE} -version
    RESULT_VARIABLE lrelease_ret)
  if(NOT lrelease_ret EQUAL "0")
    set(ts_files "")
    message(WARNING "lrelease program not working, translation files not built")
  else()
    file(GLOB ts_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.ts)
    foreach(ts_file ${ts_files})
      string(REPLACE ".ts" ".qm" qm_file "${ts_file}")
      add_custom_command(TARGET generate_translations_header
        PRE_BUILD
        COMMAND ${LRELEASE} "${CMAKE_CURRENT_SOURCE_DIR}/${ts_file}" -qm "${qm_file}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BIN_DIR}")
    endforeach()
  endif()
endif()

string(REPLACE ".ts" ".qm" qm_files "${ts_files}")

add_custom_command(TARGET generate_translations_header
  POST_BUILD
  COMMAND generate_translations_header ${qm_files}
  WORKING_DIRECTORY "${CMAKE_CURRENT_BIN_DIR}"
  COMMENT "Generating embedded translations header")
