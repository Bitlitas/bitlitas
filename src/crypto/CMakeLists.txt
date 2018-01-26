# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(crypto_sources
  aesb.c
  blake256.c
  chacha.c
  crypto-ops-data.c
  crypto-ops.c
  crypto.cpp
  groestl.c
  hash-extra-blake.c
  hash-extra-groestl.c
  hash-extra-jh.c
  hash-extra-skein.c
  hash.c
  jh.c
  keccak.c
  oaes_lib.c
  random.c
  skein.c
  slow-hash.c
  tree-hash.c)

set(crypto_headers)

set(crypto_private_headers
  blake256.h
  chacha.h
  crypto-ops.h
  crypto.h
  generic-ops.h
  groestl.h
  groestl_tables.h
  hash-ops.h
  hash.h
  initializer.h
  jh.h
  keccak.h
  oaes_config.h
  oaes_lib.h
  random.h
  skein.h
  skein_port.h)

bitlitas_private_headers(cncrypto
  ${crypto_private_headers})
bitlitas_add_library(cncrypto
  ${crypto_sources}
  ${crypto_headers}
  ${crypto_private_headers})
target_link_libraries(cncrypto
  PUBLIC
    epee
    ${Boost_SYSTEM_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

if (ARM)
  option(NO_OPTIMIZED_MULTIPLY_ON_ARM
	   "Compute multiply using generic C implementation instead of ARM ASM" OFF)
  if(NO_OPTIMIZED_MULTIPLY_ON_ARM)
    message(STATUS "Using generic C implementation for multiply")
    set_property(SOURCE slow-hash.c
      PROPERTY COMPILE_DEFINITIONS "NO_OPTIMIZED_MULTIPLY_ON_ARM")
  endif()
endif()

# Because of the way Qt works on android with JNI, the code does not live in the main android thread
# So this code runs with a 1 MB default stack size. 
# This will force the use of the heap for the allocation of the scratchpad
if (ANDROID OR IOS)
  if( BUILD_GUI_DEPS )
    add_definitions(-DFORCE_USE_HEAP=1)
  endif()
endif()


