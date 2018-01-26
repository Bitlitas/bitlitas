# Copyright (c) 2018, Bitlitas
# All rights reserved.

add_library(epee STATIC hex.cpp http_auth.cpp mlog.cpp net_utils_base.cpp string_tools.cpp wipeable_string.cpp memwipe.c
    connection_basic.cpp network_throttle.cpp network_throttle-detail.cpp)
if (USE_READLINE AND GNU_READLINE_FOUND)
  add_library(epee_readline STATIC readline_buffer.cpp)
endif()

if(HAVE_C11)
SET_PROPERTY(SOURCE memwipe.c PROPERTY COMPILE_FLAGS -std=c11)
endif()

# Build and install libepee if we're building for GUI
if (BUILD_GUI_DEPS)
    if(IOS)
        set(lib_folder lib-${ARCH})
    else()
        set(lib_folder lib)
    endif()
    install(TARGETS epee
        ARCHIVE DESTINATION ${lib_folder})
    if (USE_READLINE AND GNU_READLINE_FOUND)
      install(TARGETS epee_readline
          ARCHIVE DESTINATION ${lib_folder})
    endif()
endif()

target_link_libraries(epee
  PUBLIC
    easylogging
    ${Boost_FILESYSTEM_LIBRARY}
  PRIVATE
    ${OPENSSL_LIBRARIES}
    ${EXTRA_LIBRARIES})

if (USE_READLINE AND GNU_READLINE_FOUND)
  target_link_libraries(epee_readline
    PUBLIC
      easylogging
    PRIVATE
      ${GNU_READLINE_LIBRARY})
endif()
