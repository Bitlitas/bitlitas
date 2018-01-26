// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "cryptonote_basic/blobdatatype.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "fuzzer.h"

class TransactionFuzzer: public Fuzzer
{
public:
  virtual int run(const std::string &filename);

private:
};

int TransactionFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  cryptonote::transaction tx = AUTO_VAL_INIT(tx);
  if(!parse_and_validate_tx_from_blob(s, tx))
  {
    std::cout << "Error: failed to parse transaction from file  " << filename << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, const char **argv)
{
  TransactionFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}
