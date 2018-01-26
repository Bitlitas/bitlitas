# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(ringct_sources
  rctOps.cpp
  rctSigs.cpp
  rctTypes.cpp
  rctCryptoOps.c
  bulletproofs.cc)

set(ringct_headers)

set(ringct_private_headers
  rctOps.h
  rctSigs.h
  rctTypes.h
  bulletproofs.h)

bitlitas_private_headers(ringct
  ${crypto_private_headers})
bitlitas_add_library(ringct
  ${ringct_sources}
  ${ringct_headers}
  ${ringct_private_headers})
target_link_libraries(ringct
  PUBLIC
    common
    cncrypto
    cryptonote_basic
  PRIVATE
    ${OPENSSL_LIBRARIES}
    ${EXTRA_LIBRARIES})
