# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(crypto_sources
  crypto-ops-data.c
  crypto-ops.c
  crypto.cpp
  hash.c
  main.cpp
  random.c)

set(crypto_headers
  crypto-tests.h)

add_executable(cncrypto-tests
  ${crypto_sources}
  ${crypto_headers})
target_link_libraries(cncrypto-tests
  PRIVATE
    common
    ${Boost_SYSTEM_LIBRARY}
    ${EXTRA_LIBRARIES})
set_property(TARGET cncrypto-tests
  PROPERTY
    FOLDER "tests")

add_test(
  NAME    cncrypto
  COMMAND cncrypto-tests "${CMAKE_CURRENT_SOURCE_DIR}/tests.txt")
