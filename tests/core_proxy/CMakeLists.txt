# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(core_proxy_sources
  core_proxy.cpp)

set(core_proxy_headers
  core_proxy.h)

add_executable(core_proxy
  ${core_proxy_sources}
  ${core_proxy_headers})
target_link_libraries(core_proxy
  PRIVATE
    cryptonote_core
    cryptonote_protocol
    p2p
    version
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET core_proxy
  PROPERTY
    FOLDER "tests")
