# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(blocksdat "")
if(PER_BLOCK_CHECKPOINT)
  if(APPLE)
    add_custom_command(OUTPUT blocksdat.o MAIN_DEPENDENCY ../blocks/checkpoints.dat COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && touch stub.c && ${CMAKE_C_COMPILER} -o stub.o -c stub.c COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ${CMAKE_LINKER} ${LD_RAW_FLAGS} -r -sectcreate __DATA __blocks_dat ../blocks/checkpoints.dat -o ${CMAKE_CURRENT_BINARY_DIR}/blocksdat.o stub.o && rm -f stub.*)
  else()
    add_custom_command(OUTPUT blocksdat.o MAIN_DEPENDENCY ../blocks/checkpoints.dat COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && cp ../blocks/checkpoints.dat blocks.dat && ${CMAKE_LINKER} ${LD_RAW_FLAGS} -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/blocksdat.o blocks.dat && rm -f blocks.dat)
  endif()
  set(blocksdat "blocksdat.o")
endif()

set(daemon_sources
  command_parser_executor.cpp
  command_server.cpp
  daemon.cpp
  executor.cpp
  main.cpp
  rpc_command_executor.cpp
)

set(daemon_headers)

set(daemon_private_headers
  command_parser_executor.h
  command_server.h
  core.h
  daemon.h
  executor.h
  p2p.h
  protocol.h
  rpc.h
  rpc_command_executor.h

  # cryptonote_protocol
  ../cryptonote_protocol/cryptonote_protocol_defs.h
  ../cryptonote_protocol/cryptonote_protocol_handler.h
  ../cryptonote_protocol/cryptonote_protocol_handler.inl
  ../cryptonote_protocol/cryptonote_protocol_handler_common.h

  # p2p
  ../p2p/net_node.h
  ../p2p/net_node_common.h
  ../p2p/net_peerlist.h
  ../p2p/net_peerlist_boost_serialization.h
  ../p2p/p2p_protocol_defs.h
  ../p2p/stdafx.h)

bitlitas_private_headers(daemon
  ${daemon_private_headers})
bitlitas_add_executable(daemon
  ${daemon_sources}
  ${daemon_headers}
  ${daemon_private_headers}
  ${blocksdat}
)
target_link_libraries(daemon
  PRIVATE
    rpc
    blockchain_db
    cryptonote_core
    cncrypto
    common
    p2p
    cryptonote_protocol
    daemonizer
    serialization
    daemon_rpc_server
    epee
    ${EPEE_READLINE}
    version
    ${Boost_CHRONO_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${ZMQ_LIB}
    ${GNU_READLINE_LIBRARY}
    ${EXTRA_LIBRARIES})
set_property(TARGET daemon
  PROPERTY
    OUTPUT_NAME "bitlitasd")
install(TARGETS daemon DESTINATION bin)
