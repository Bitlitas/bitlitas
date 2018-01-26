# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(cn_deserialize_sources
  cn_deserialize.cpp
  )

bitlitas_add_executable(cn_deserialize
  ${cn_deserialize_sources}
  ${cn_deserialize_private_headers})

target_link_libraries(cn_deserialize
  LINK_PRIVATE
    cryptonote_core
    blockchain_db
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET cn_deserialize
	PROPERTY
	OUTPUT_NAME "bitlitas-utils-deserialize")


set(object_sizes_sources
  object_sizes.cpp
  )

bitlitas_add_executable(object_sizes
  ${object_sizes_sources}
  ${object_sizes_private_headers})

target_link_libraries(object_sizes
  LINK_PRIVATE
    cryptonote_core
    blockchain_db
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET object_sizes
	PROPERTY
	OUTPUT_NAME "bitlitas-utils-object-sizes")

