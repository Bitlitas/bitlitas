// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "net/net_parse_helpers.h"
#include "fuzzer.h"

class ParseURLFuzzer: public Fuzzer
{
public:
  ParseURLFuzzer() {}
  virtual int init();
  virtual int run(const std::string &filename);
};

int ParseURLFuzzer::init()
{
  return 0;
}

int ParseURLFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  try
  {
    epee::net_utils::http::url_content url;
    epee::net_utils::parse_url(s, url);
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
  ParseURLFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}

