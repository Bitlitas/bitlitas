// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#ifndef BITLITAS_EXCEPTION_H
#define BITLITAS_EXCEPTION_H

#include <string>

namespace tools
{

void set_stack_trace_log(const std::string &log);
void log_stack_trace(const char *msg);

}  // namespace tools

#endif
