// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once
#include <string>

#ifndef WIN32

namespace posix {

void fork(const std::string & pidfile);

}

#endif
