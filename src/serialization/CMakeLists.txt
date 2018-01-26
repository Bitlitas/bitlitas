# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(serialization_sources
  json_object.cpp)

set(serialization_headers)

set(serialization_private_headers
  json_object.h)

bitlitas_private_headers(serialization
  ${serialization_private_headers})
bitlitas_add_library(serialization
  ${serialization_sources}
  ${serialization_headers}
  ${serialization_private_headers})
target_link_libraries(serialization
  LINK_PRIVATE
    cryptonote_core
    cryptonote_protocol
    ${Boost_CHRONO_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${EXTRA_LIBRARIES})
add_dependencies(serialization
  version)

