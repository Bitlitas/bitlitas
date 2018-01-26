# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(blockchain_db_sources
  blockchain_db.cpp
  lmdb/db_lmdb.cpp
  )

if (BERKELEY_DB)
  set(blockchain_db_sources
  ${blockchain_db_sources}
  berkeleydb/db_bdb.cpp
  )
endif()


set(blockchain_db_headers)

set(blockchain_db_private_headers
  blockchain_db.h
  lmdb/db_lmdb.h
  )

if (BERKELEY_DB)
  set(blockchain_db_private_headers
  ${blockchain_db_private_headers}
  berkeleydb/db_bdb.h
  )
endif()

bitlitas_private_headers(blockchain_db
  ${crypto_private_headers})
bitlitas_add_library(blockchain_db
  ${blockchain_db_sources}
  ${blockchain_db_headers}
  ${blockchain_db_private_headers})
target_link_libraries(blockchain_db
  PUBLIC
    common
    cncrypto
    ringct
    ${LMDB_LIBRARY}
    ${BDB_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})
