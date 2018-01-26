# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})

set(common_sources
  base58.cpp
  command_line.cpp
  dns_utils.cpp
  download.cpp
  util.cpp
  i18n.cpp
  password.cpp
  perf_timer.cpp
  threadpool.cpp
  updates.cpp)

if (STACK_TRACE)
  list(APPEND common_sources stack_trace.cpp)
endif()

set(common_headers)

set(common_private_headers
  apply_permutation.h
  base58.h
  boost_serialization_helper.h
  command_line.h
  common_fwd.h
  dns_utils.h
  download.h
  http_connection.h
  int-util.h
  pod-class.h
  rpc_client.h
  scoped_message_writer.h
  unordered_containers_boost_serialization.h
  util.h
  varint.h
  i18n.h
  password.h
  perf_timer.h
  stack_trace.h
  threadpool.h
  updates.h)

bitlitas_private_headers(common
  ${common_private_headers})
bitlitas_add_library(common
  ${common_sources}
  ${common_headers}
  ${common_private_headers}
  DEPENDS generate_translations_header)
target_link_libraries(common
  PUBLIC
    epee
    cncrypto
    ${UNBOUND_LIBRARY}
    ${LIBUNWIND_LIBRARIES}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
  PRIVATE
    ${OPENSSL_LIBRARIES}
    ${EXTRA_LIBRARIES})

#bitlitas_install_headers(common
#  ${common_headers})
