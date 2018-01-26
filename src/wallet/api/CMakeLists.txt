# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

# include (${PROJECT_SOURCE_DIR}/cmake/libutils.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(wallet_api_sources
  wallet.cpp
  wallet_manager.cpp
  transaction_info.cpp
  transaction_history.cpp
  pending_transaction.cpp
  utils.cpp
  address_book.cpp
  subaddress.cpp
  subaddress_account.cpp
  unsigned_transaction.cpp)

set(wallet_api_headers
    wallet2_api.h)

set(wallet_api_private_headers
  wallet.h
  wallet_manager.h
  transaction_info.h
  transaction_history.h
  pending_transaction.h
  common_defines.h
  address_book.h
  subaddress.h
  subaddress_account.h
  unsigned_transaction.h)

bitlitas_private_headers(wallet_api
  ${wallet_api_private_headers})
bitlitas_add_library(wallet_api
  ${wallet_api_sources}
  ${wallet_api_headers}
  ${wallet_api_private_headers})
target_link_libraries(wallet_api
  PUBLIC
    wallet
    common
    cryptonote_core
    mnemonics
    ${Boost_CHRONO_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})


if(IOS)
    set(lib_folder lib-${ARCH})
else()
    set(lib_folder lib)
endif()

install(FILES ${wallet_api_headers}
    DESTINATION include/wallet)
