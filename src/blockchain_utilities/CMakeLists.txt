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

set(blockchain_import_sources
  blockchain_import.cpp
  bootstrap_file.cpp
  blocksdat_file.cpp
  )

set(blockchain_import_private_headers
  bootstrap_file.h
  blocksdat_file.h
  bootstrap_serialization.h
  )

bitlitas_private_headers(blockchain_import
	  ${blockchain_import_private_headers})

set(blockchain_export_sources
  blockchain_export.cpp
  bootstrap_file.cpp
  blocksdat_file.cpp
  )

set(blockchain_export_private_headers
  bootstrap_file.h
  blocksdat_file.h
  bootstrap_serialization.h
  )

bitlitas_private_headers(blockchain_export
	  ${blockchain_export_private_headers})


bitlitas_add_executable(blockchain_import
  ${blockchain_import_sources}
  ${blockchain_import_private_headers}
  ${blocksdat})

target_link_libraries(blockchain_import
  PRIVATE
    cryptonote_core
    blockchain_db
    p2p
    version
    epee
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})

if(ARCH_WIDTH)
  target_compile_definitions(blockchain_import
    PUBLIC -DARCH_WIDTH=${ARCH_WIDTH})
endif()

set_property(TARGET blockchain_import
	PROPERTY
	OUTPUT_NAME "bitlitas-blockchain-import")
install(TARGETS blockchain_import DESTINATION bin)

bitlitas_add_executable(blockchain_export
  ${blockchain_export_sources}
  ${blockchain_export_private_headers})

target_link_libraries(blockchain_export
  PRIVATE
    cryptonote_core
    blockchain_db
    p2p
    version
    epee
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})

set_property(TARGET blockchain_export
	PROPERTY
	OUTPUT_NAME "bitlitas-blockchain-export")
install(TARGETS blockchain_export DESTINATION bin)

