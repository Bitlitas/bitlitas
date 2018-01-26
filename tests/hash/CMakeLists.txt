# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(hash_sources
  main.cpp)

set(hash_headers)

add_executable(hash-tests
  ${hash_sources}
  ${hash_headers})
target_link_libraries(hash-tests
  PRIVATE
    common
    cncrypto
    ${EXTRA_LIBRARIES})
set_property(TARGET hash-tests
  PROPERTY
    FOLDER "tests")

foreach (hash IN ITEMS fast slow tree extra-blake extra-groestl extra-jh extra-skein)
  add_test(
    NAME    "hash-${hash}"
    COMMAND hash-tests "${hash}" "${CMAKE_CURRENT_SOURCE_DIR}/tests-${hash}.txt")
endforeach ()
