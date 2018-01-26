// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "cryptonote_basic/blobdatatype.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "wallet/wallet2.h"
#include "fuzzer.h"

class ColdOutputsFuzzer: public Fuzzer
{
public:
  ColdOutputsFuzzer(): wallet(true) {}
  virtual int init();
  virtual int run(const std::string &filename);

private:
  tools::wallet2 wallet;
};

int ColdOutputsFuzzer::init()
{
  static const char * const spendkey_hex = "0b4f47697ec99c3de6579304e5f25c68b07afbe55b71d99620bf6cbf4e45a80f";
  crypto::secret_key spendkey;
  epee::string_tools::hex_to_pod(spendkey_hex, spendkey);

  try
  {
    wallet.init("");
    wallet.generate("", "", spendkey, true, false);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error on ColdOutputsFuzzer::init: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

int ColdOutputsFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  s = std::string("\x01\x16serialization::archive") + s;
  try
  {
    std::vector<tools::wallet2::transfer_details> outputs;
    std::stringstream iss;
    iss << s;
    boost::archive::portable_binary_iarchive ar(iss);
    ar >> outputs;
    size_t n_outputs = wallet.import_outputs(outputs);
    std::cout << boost::lexical_cast<std::string>(n_outputs) << " outputs imported" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Failed to import outputs: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, const char **argv)
{
  ColdOutputsFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}

