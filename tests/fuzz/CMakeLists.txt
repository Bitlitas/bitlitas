# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

add_executable(block_fuzz_tests block.cpp fuzzer.cpp)
target_link_libraries(block_fuzz_tests
  PRIVATE
    cryptonote_core
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET block_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(transaction_fuzz_tests transaction.cpp fuzzer.cpp)
target_link_libraries(transaction_fuzz_tests
  PRIVATE
    cryptonote_core
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET transaction_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(signature_fuzz_tests signature.cpp fuzzer.cpp)
target_link_libraries(signature_fuzz_tests
  PRIVATE
    wallet
    cryptonote_core
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET signature_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(cold-outputs_fuzz_tests cold-outputs.cpp fuzzer.cpp)
target_link_libraries(cold-outputs_fuzz_tests
  PRIVATE
    wallet
    cryptonote_core
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET cold-outputs_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(cold-transaction_fuzz_tests cold-transaction.cpp fuzzer.cpp)
target_link_libraries(cold-transaction_fuzz_tests
  PRIVATE
    wallet
    cryptonote_core
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET cold-transaction_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(load-from-binary_fuzz_tests load_from_binary.cpp fuzzer.cpp)
target_link_libraries(load-from-binary_fuzz_tests
  PRIVATE
    common
    epee
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET load-from-binary_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(load-from-json_fuzz_tests load_from_json.cpp fuzzer.cpp)
target_link_libraries(load-from-json_fuzz_tests
  PRIVATE
    common
    epee
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET load-from-json_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(base58_fuzz_tests base58.cpp fuzzer.cpp)
target_link_libraries(base58_fuzz_tests
  PRIVATE
    common
    epee
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET base58_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(parse-url_fuzz_tests parse_url.cpp fuzzer.cpp)
target_link_libraries(parse-url_fuzz_tests
  PRIVATE
    epee
    ${Boost_REGEX_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET parse-url_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(http-client_fuzz_tests http-client.cpp fuzzer.cpp)
target_link_libraries(http-client_fuzz_tests
  PRIVATE
    epee
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET http-client_fuzz_tests
  PROPERTY
    FOLDER "tests")

add_executable(levin_fuzz_tests levin.cpp fuzzer.cpp)
target_link_libraries(levin_fuzz_tests
  PRIVATE
    common
    epee
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
set_property(TARGET levin_fuzz_tests
  PROPERTY
    FOLDER "tests")

