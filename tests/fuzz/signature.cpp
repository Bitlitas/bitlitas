// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "cryptonote_basic/blobdatatype.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "wallet/wallet2.h"
#include "fuzzer.h"

class SignatureFuzzer: public Fuzzer
{
public:
  SignatureFuzzer(): Fuzzer(), wallet(true) {}
  virtual int init();
  virtual int run(const std::string &filename);

private:
  tools::wallet2 wallet;
  cryptonote::account_public_address address;
};

int SignatureFuzzer::init()
{
  static const char * const spendkey_hex = "0b4f47697ec99c3de6579304e5f25c68b07afbe55b71d99620bf6cbf4e45a80f";
  crypto::secret_key spendkey;
  epee::string_tools::hex_to_pod(spendkey_hex, spendkey);

  try
  {
    wallet.init("");
    wallet.generate("", "", spendkey, true, false);

    cryptonote::address_parse_info info;
    if (!cryptonote::get_account_address_from_str_or_url(info, true, "9uVsvEryzpN8WH2t1WWhFFCG5tS8cBNdmJYNRuckLENFimfauV5pZKeS1P2CbxGkSDTUPHXWwiYE5ZGSXDAGbaZgDxobqDN"))
    {
      std::cerr << "failed to parse address" << std::endl;
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error on SignatureFuzzer::init: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

int SignatureFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }

  bool valid = wallet.verify("test", address, s);
  std::cout << "Signature " << (valid ? "valid" : "invalid") << std::endl;

  return 0;
}

int main(int argc, const char **argv)
{
  SignatureFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}
