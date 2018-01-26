# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(transfers_sources
  transfers.cpp)

set(transfers_headers)

add_executable(transfers
  ${transfers_sources}
  ${transfers_headers})
target_link_libraries(transfers
  PRIVATE
    useragent
    rpc
    cryptonote_core
    cncrypto
    common
    epee
    ${GTEST_LIBRARIES})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test_transfers")
add_custom_target(test_transfers
  COMMAND           transfers
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test_transfers")
