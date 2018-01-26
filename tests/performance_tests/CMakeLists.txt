# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(performance_tests_sources
  main.cpp)

set(performance_tests_headers
  check_tx_signature.h
  cn_slow_hash.h
  construct_tx.h
  derive_public_key.h
  derive_secret_key.h
  ge_frombytes_vartime.h
  generate_key_derivation.h
  generate_key_image.h
  generate_key_image_helper.h
  generate_keypair.h
  is_out_to_acc.h
  subaddress_expand.h
  multi_tx_test_base.h
  performance_tests.h
  performance_utils.h
  single_tx_test_base.h)

add_executable(performance_tests
  ${performance_tests_sources}
  ${performance_tests_headers})
target_link_libraries(performance_tests
  PRIVATE
    wallet
    cryptonote_core
    common
    cncrypto
    epee
    ${Boost_CHRONO_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET performance_tests
  PROPERTY
    FOLDER "tests")
