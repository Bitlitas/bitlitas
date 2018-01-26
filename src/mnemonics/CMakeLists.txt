# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

set(mnemonics_sources
  electrum-words.cpp)

set(mnemonics_headers)

set(mnemonics_private_headers
  electrum-words.h
  chinese_simplified.h
  english.h
  dutch.h
  french.h
  german.h
  italian.h
  japanese.h
  lithuanian.h
  language_base.h
  english_old.h
  portuguese.h
  russian.h
  singleton.h
  spanish.h
  esperanto.h
  lojban.h)

bitlitas_private_headers(mnemonics
  ${mnemonics_private_headers})
bitlitas_add_library(mnemonics
  ${mnemonics_sources}
  ${mnemonics_headers}
  ${mnemonics_private_headers})
target_link_libraries(mnemonics
  PUBLIC
    epee
    easylogging
    ${Boost_SYSTEM_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})
