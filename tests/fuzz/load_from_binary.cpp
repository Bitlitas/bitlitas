// Copyright (c) 2018, Bitlitas 
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "serialization/keyvalue_serialization.h"
#include "storages/portable_storage_template_helper.h"
#include "storages/portable_storage_base.h"
#include "fuzzer.h"

class PortableStorageFuzzer: public Fuzzer
{
public:
  PortableStorageFuzzer() {}
  virtual int init();
  virtual int run(const std::string &filename);
};

int PortableStorageFuzzer::init()
{
  return 0;
}

int PortableStorageFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  try
  {
    epee::serialization::portable_storage ps;
    ps.load_from_binary(s);
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
  PortableStorageFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}

