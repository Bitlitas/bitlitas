# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

cmake_minimum_required (VERSION 2.6)
project (bitlitas CXX)

file(GLOB P2P *)
source_group(p2p FILES ${P2P})

#add_library(p2p ${P2P})

#bitlitas_private_headers(p2p ${P2P})
bitlitas_add_library(p2p ${P2P})
target_link_libraries(p2p
  PUBLIC
    epee
    version
    ${UPNP_LIBRARIES}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})
