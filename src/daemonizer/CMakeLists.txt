# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

if(MSVC OR MINGW)
  set(daemonizer_sources
    windows_service.cpp
    windows_daemonizer.inl
  )
else()
  set(daemonizer_sources
    posix_fork.cpp
    posix_daemonizer.inl
  )
endif()

set(daemonizer_headers
)

if(MSVC OR MINGW)
  set(daemonizer_private_headers
    daemonizer.h
    windows_service.h
    windows_service_runner.h
  )
else()
  set(daemonizer_private_headers
    daemonizer.h
    posix_fork.h
  )
endif()

bitlitas_private_headers(daemonizer
  ${daemonizer_private_headers})
bitlitas_add_library(daemonizer
  ${daemonizer_sources}
  ${daemonizer_headers}
  ${daemonizer_private_headers})
target_link_libraries(daemonizer
  PUBLIC
    common
    ${Boost_CHRONO_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})
