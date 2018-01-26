# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

if(APPLE)
    add_library(blocks STATIC blockexports.c)
    set_target_properties(blocks PROPERTIES LINKER_LANGUAGE C)
else()
    add_custom_command(OUTPUT blocks.o MAIN_DEPENDENCY blocks.dat COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ${CMAKE_LINKER} ${LD_RAW_FLAGS} -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/blocks.o blocks.dat)
    add_custom_command(OUTPUT testnet_blocks.o MAIN_DEPENDENCY testnet_blocks.dat COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ${CMAKE_LINKER} ${LD_RAW_FLAGS} -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/testnet_blocks.o testnet_blocks.dat)
    add_library(blocks STATIC blocks.o testnet_blocks.o blockexports.c)
    set_target_properties(blocks PROPERTIES LINKER_LANGUAGE C)
endif()

