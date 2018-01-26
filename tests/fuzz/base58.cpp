// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "common/base58.h"
#include "fuzzer.h"

class Base58Fuzzer: public Fuzzer
{
public:
  Base58Fuzzer() {}
  virtual int init();
  virtual int run(const std::string &filename);
};

int Base58Fuzzer::init()
{
  return 0;
}

int Base58Fuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  try
  {
    std::string data;
    tools::base58::decode(s, data);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Failed to load from binary: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, const char **argv)
{
  Base58Fuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}

