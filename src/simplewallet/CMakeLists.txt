# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(simplewallet_sources
  simplewallet.cpp)

set(simplewallet_headers)

set(simplewallet_private_headers
  simplewallet.h)

bitlitas_private_headers(simplewallet
  ${simplewallet_private_headers})
bitlitas_add_executable(simplewallet
  ${simplewallet_sources}
  ${simplewallet_headers}
  ${simplewallet_private_headers})
target_link_libraries(simplewallet
  PRIVATE
    wallet
    rpc_base
    cryptonote_core
    cncrypto
    common
    mnemonics
    epee
    ${EPEE_READLINE}
    version
    ${Boost_CHRONO_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GNU_READLINE_LIBRARY}
    ${EXTRA_LIBRARIES})
set_property(TARGET simplewallet
  PROPERTY
    OUTPUT_NAME "bitlitas-wallet-cli")
install(TARGETS simplewallet DESTINATION bin)
