// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "cryptonote_basic/blobdatatype.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "fuzzer.h"

class BlockFuzzer: public Fuzzer
{
public:
  virtual int run(const std::string &filename);

private:
};

int BlockFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  cryptonote::block b = AUTO_VAL_INIT(b);
  if(!parse_and_validate_block_from_blob(s, b))
  {
    std::cout << "Error: failed to parse block from file  " << filename << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, const char **argv)
{
  BlockFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}
