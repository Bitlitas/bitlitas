# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(functional_tests_sources
  main.cpp
  transactions_flow_test.cpp
  transactions_generation_from_blockchain.cpp)

set(functional_tests_headers
  transactions_flow_test.h
  transactions_generation_from_blockchain.h)

add_executable(functional_tests
  ${functional_tests_sources}
  ${functional_tests_headers})
target_link_libraries(functional_tests
  PRIVATE
    cryptonote_core
    wallet
    common
    cncrypto
    epee
    ${Boost_REGEX_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET functional_tests
  PROPERTY
    FOLDER "tests")
