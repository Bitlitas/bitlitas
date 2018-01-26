# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(difficulty_sources
  difficulty.cpp)

set(difficulty_headers)

add_executable(difficulty-tests
  ${difficulty_sources}
  ${difficulty_headers})
target_link_libraries(difficulty-tests
  PRIVATE
    cryptonote_core
    ${EXTRA_LIBRARIES})
set_property(TARGET difficulty-tests
  PROPERTY
    FOLDER "tests")

add_test(
  NAME    difficulty
  COMMAND difficulty-tests "${CMAKE_CURRENT_SOURCE_DIR}/data.txt")
