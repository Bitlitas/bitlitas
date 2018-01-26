# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

if(APPLE)
  find_library(IOKIT_LIBRARY IOKit)
  mark_as_advanced(IOKIT_LIBRARY)
  list(APPEND EXTRA_LIBRARIES ${IOKIT_LIBRARY})
endif()

set(checkpoints_sources
  checkpoints.cpp)

set(checkpoints_headers)

set(checkpoints_private_headers
  checkpoints.h)

bitlitas_private_headers(checkpoints
  ${checkpoints_private_headers})
bitlitas_add_library(checkpoints
  ${checkpoints_sources}
  ${checkpoints_headers}
  ${checkpoints_private_headers})
target_link_libraries(checkpoints
  PUBLIC
    common
    cncrypto
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})
