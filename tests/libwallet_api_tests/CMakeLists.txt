# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(libwallet_api_tests_sources
  main.cpp
)

set(libwallet_api_tests_headers
  )

add_executable(libwallet_api_tests
  ${libwallet_api_tests_sources}
  ${libwallet_api_tests_headers})

target_link_libraries(libwallet_api_tests
  PRIVATE
    wallet_api
    wallet
    version
    epee
    ${Boost_CHRONO_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})

set_property(TARGET libwallet_api_tests
  PROPERTY
    FOLDER "tests")

if (NOT MSVC)
  set_property(TARGET libwallet_api_tests
    APPEND_STRING
    PROPERTY
      COMPILE_FLAGS " -Wno-undef -Wno-sign-compare")
endif ()

add_test(
  NAME    libwallet_api_tests
  COMMAND libwallet_api_tests)
