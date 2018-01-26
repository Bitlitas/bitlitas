# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(rpc_base_sources
  rpc_args.cpp)

set(rpc_sources
  core_rpc_server.cpp
  instanciations)

set(daemon_messages_sources
  message.cpp
  daemon_messages.cpp)

set(daemon_rpc_server_sources
  daemon_handler.cpp
  zmq_server.cpp)


set(rpc_base_headers
  rpc_args.h)

set(rpc_headers)

set(daemon_rpc_server_headers)


set(rpc_daemon_private_headers
  core_rpc_server.h
  core_rpc_server_commands_defs.h
  core_rpc_server_error_codes.h)

set(daemon_messages_private_headers
  message.h
  daemon_messages.h)

set(daemon_rpc_server_private_headers
  message.h
  daemon_messages.h
  daemon_handler.h
  rpc_handler.h
  zmq_server.h)


bitlitas_private_headers(rpc
  ${rpc_private_headers})

bitlitas_private_headers(daemon_rpc_server
  ${daemon_rpc_server_private_headers})


bitlitas_add_library(rpc_base
  ${rpc_base_sources}
  ${rpc_base_headers}
  ${rpc_base_private_headers})

bitlitas_add_library(rpc
  ${rpc_sources}
  ${rpc_headers}
  ${rpc_private_headers})

bitlitas_add_library(daemon_messages
  ${daemon_messages_sources}
  ${daemon_messages_headers}
  ${daemon_messages_private_headers})

bitlitas_add_library(daemon_rpc_server
  ${daemon_rpc_server_sources}
  ${daemon_rpc_server_headers}
  ${daemon_rpc_server_private_headers})


target_link_libraries(rpc_base
  PUBLIC
    common
    epee
    ${Boost_REGEX_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

target_link_libraries(rpc
  PUBLIC
    rpc_base
    common
    cryptonote_core
    cryptonote_protocol
    epee
    ${Boost_REGEX_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

target_link_libraries(daemon_messages
  LINK_PRIVATE
    cryptonote_core
    cryptonote_protocol
    serialization
    ${EXTRA_LIBRARIES})

target_link_libraries(daemon_rpc_server
  LINK_PRIVATE
    rpc
    cryptonote_core
    cryptonote_protocol
    daemon_messages
    serialization
    ${Boost_CHRONO_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${ZMQ_LIB}
    ${EXTRA_LIBRARIES})
target_include_directories(daemon_rpc_server PUBLIC ${ZMQ_INCLUDE_PATH})
target_include_directories(obj_daemon_rpc_server PUBLIC ${ZMQ_INCLUDE_PATH})
