# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

cmake_minimum_required (VERSION 2.6)
project (bitlitas CXX)

file(GLOB CRYPTONOTE_PROTOCOL *)
source_group(cryptonote_protocol FILES ${CRYPTONOTE_PROTOCOL})

#bitlitas_private_headers(cryptonote_protocol ${CRYPTONOTE_PROTOCOL})
bitlitas_add_library(cryptonote_protocol ${CRYPTONOTE_PROTOCOL})
target_link_libraries(cryptonote_protocol
  PUBLIC
    p2p
  PRIVATE
    ${EXTRA_LIBRARIES})
