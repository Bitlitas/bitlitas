// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <string>

class Fuzzer
{
public:
  virtual int init() { return 0; }
  virtual int run(const std::string &filename) = 0;
};

int run_fuzzer(int argc, const char **argv, Fuzzer &fuzzer);
