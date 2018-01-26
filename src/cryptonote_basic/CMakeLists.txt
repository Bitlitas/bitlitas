# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

if(APPLE)
  find_library(IOKIT_LIBRARY IOKit)
  mark_as_advanced(IOKIT_LIBRARY)
  list(APPEND EXTRA_LIBRARIES ${IOKIT_LIBRARY})
endif()

set(cryptonote_basic_sources
  account.cpp
  cryptonote_basic_impl.cpp
  cryptonote_format_utils.cpp
  difficulty.cpp
  hardfork.cpp
  miner.cpp)

set(cryptonote_basic_headers)

set(cryptonote_basic_private_headers
  account.h
  account_boost_serialization.h
  connection_context.h
  cryptonote_basic.h
  cryptonote_basic_impl.h
  cryptonote_boost_serialization.h
  cryptonote_format_utils.h
  cryptonote_stat_info.h
  difficulty.h
  hardfork.h
  miner.h
  tx_extra.h
  verification_context.h)

bitlitas_private_headers(cryptonote_basic
  ${cryptonote_basic_private_headers})
bitlitas_add_library(cryptonote_basic
  ${cryptonote_basic_sources}
  ${cryptonote_basic_headers}
  ${cryptonote_basic_private_headers})
target_link_libraries(cryptonote_basic
  PUBLIC
    common
    cncrypto
    checkpoints
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})
