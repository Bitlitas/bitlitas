# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

# warnings are cleared only for GCC on Linux
if (NOT (MINGW OR APPLE OR FREEBSD OR OPENBSD OR DRAGONFLY))
  add_compile_options("${WARNINGS_AS_ERRORS_FLAG}") # applies only to targets that follow
endif()

add_subdirectory(epee)

