# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(core_tests_sources
  block_reward.cpp
  block_validation.cpp
  chain_split_1.cpp
  chain_switch_1.cpp
  chaingen.cpp
  chaingen001.cpp
  chaingen_main.cpp
  double_spend.cpp
  integer_overflow.cpp
  multisig.cpp
  ring_signature_1.cpp
  transaction_tests.cpp
  tx_validation.cpp
  v2_tests.cpp
  rct.cpp)

set(core_tests_headers
  block_reward.h
  block_validation.h
  chain_split_1.h
  chain_switch_1.h
  chaingen.h
  chaingen_tests_list.h
  double_spend.h
  double_spend.inl
  integer_overflow.h
  multisig.h
  ring_signature_1.h
  transaction_tests.h
  tx_validation.h
  v2_tests.h
  rct.h)

add_executable(core_tests
  ${core_tests_sources}
  ${core_tests_headers})
target_link_libraries(core_tests
  PRIVATE
    multisig
    cryptonote_core
    p2p
    version
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET core_tests
  PROPERTY
    FOLDER "tests")

add_test(
  NAME    core_tests
  COMMAND core_tests --generate_and_play_test_data)
