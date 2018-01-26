# Copyright (c) 2018, Bitlitas
#
# All rights reserved. Based on Cryptonote and Monero.

set(multisig_sources
  multisig.cpp)

set(multisig_headers)

set(multisig_private_headers
  multisig.h)

bitlitas_private_headers(multisig
  ${multisig_private_headers})

bitlitas_add_library(multisig
  ${multisig_sources}
  ${multisig_headers}
  ${multisig_private_headers})

target_link_libraries(multisig
  PUBLIC
    ringct
    cryptonote_basic
    common
    cncrypto
  PRIVATE
    ${EXTRA_LIBRARIES})
