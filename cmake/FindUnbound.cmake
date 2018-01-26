# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

MESSAGE(STATUS "Looking for libunbound")

FIND_PATH(UNBOUND_INCLUDE_DIR
  NAMES unbound.h
  PATH_SUFFIXES include/ include/unbound/
  PATHS "${PROJECT_SOURCE_DIR}"
  ${UNBOUND_ROOT}
  $ENV{UNBOUND_ROOT}
  /usr/local/
  /usr/
)

find_library(UNBOUND_LIBRARIES unbound)
