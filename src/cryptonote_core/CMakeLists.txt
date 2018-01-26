# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(cryptonote_core_sources
  blockchain.cpp
  cryptonote_core.cpp
  tx_pool.cpp
  cryptonote_tx_utils.cpp)

set(cryptonote_core_headers)

set(cryptonote_core_private_headers
  blockchain_storage_boost_serialization.h
  blockchain.h
  cryptonote_core.h
  tx_pool.h
  cryptonote_tx_utils.h)

if(PER_BLOCK_CHECKPOINT)
  set(Blocks "blocks")
else()
  set(Blocks "")
endif()

bitlitas_private_headers(cryptonote_core
  ${cryptonote_core_private_headers})
bitlitas_add_library(cryptonote_core
  ${cryptonote_core_sources}
  ${cryptonote_core_headers}
  ${cryptonote_core_private_headers})
target_link_libraries(cryptonote_core
  PUBLIC
    version
    common
    cncrypto
    blockchain_db
    multisig
    ringct
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  PRIVATE
    ${Blocks}
    ${EXTRA_LIBRARIES})
