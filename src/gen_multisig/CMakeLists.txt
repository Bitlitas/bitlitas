# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(gen_multisig_sources
  gen_multisig.cpp)

bitlitas_add_executable(gen_multisig
  ${gen_multisig_sources})
target_link_libraries(gen_multisig
  PRIVATE
    wallet
    cryptonote_core
    cncrypto
    common
    epee
    ${EPEE_READLINE}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GNU_READLINE_LIBRARY}
    ${EXTRA_LIBRARIES})
add_dependencies(gen_multisig
  version)
set_property(TARGET gen_multisig
  PROPERTY
    OUTPUT_NAME "bitlitas-gen-trusted-multisig")
install(TARGETS gen_multisig DESTINATION bin)
