// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"

#include <cstdint>

#include "wallet/wallet2.h"

static const struct
{
  const char *address;
  const char *spendkey;
} test_addresses[] =
{
  {
    "9uvjbU54ZJb8j7Dcq1h3F1DnBRkxXdYUX4pbJ7mE3ghM8uF3fKzqRKRNAKYZXcNLqMg7MxjVVD2wKC2PALUwEveGSC3YSWD",
    "2dd6e34a234c3e8b5d29a371789e4601e96dee4ea6f7ef79224d1a2d91164c01"
  },
  {
    "9ywDBAyDbb6QKFiZxDJ4hHZqZEQXXCR5EaYNcndUpqPDeE7rEgs6neQdZnhcDrWbURYK8xUjhuG2mVjJdmknrZbcG7NnbaB",
    "fac47aecc948ce9d3531aa042abb18235b1df632087c55a361b632ffdd6ede0c"
  },
  {
    "9t6Hn946u3eah5cuncH1hB5hGzsTUoevtf4SY7MHN5NgJZh2SFWsyVt3vUhuHyRKyrCQvr71Lfc1AevG3BXE11PQFoXDtD8",
    "bbd3175ef9fd9f5eefdc43035f882f74ad14c4cf1799d8b6f9001bc197175d02"
  }
};

static void make_wallet(unsigned int idx, tools::wallet2 &wallet)
{
  ASSERT_TRUE(idx < sizeof(test_addresses) / sizeof(test_addresses[0]));

  crypto::secret_key spendkey;
  epee::string_tools::hex_to_pod(test_addresses[idx].spendkey, spendkey);

  try
  {
    wallet.init("");
    wallet.set_subaddress_lookahead(1, 1);
    wallet.generate("", "", spendkey, true, false);
    ASSERT_TRUE(test_addresses[idx].address == wallet.get_account().get_public_address_str(true));
  }
  catch (const std::exception &e)
  {
    MFATAL("Error creating test wallet: " << e.what());
    ASSERT_TRUE(0);
  }
}

static void make_M_2_wallet(tools::wallet2 &wallet0, tools::wallet2 &wallet1, unsigned int M)
{
  ASSERT_TRUE(M <= 2);

  make_wallet(0, wallet0);
  make_wallet(1, wallet1);

  std::vector<crypto::secret_key> sk0(1), sk1(1);
  std::vector<crypto::public_key> pk0(1), pk1(1);

  std::string mi0 = wallet0.get_multisig_info();
  std::string mi1 = wallet1.get_multisig_info();

  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi1, sk0[0], pk0[0]));
  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi0, sk1[0], pk1[0]));

  ASSERT_FALSE(wallet0.multisig() || wallet1.multisig());
  wallet0.make_multisig("", sk0, pk0, M);
  wallet1.make_multisig("", sk1, pk1, M);

  ASSERT_TRUE(wallet0.get_account().get_public_address_str(true) == wallet1.get_account().get_public_address_str(true));

  bool ready;
  uint32_t threshold, total;
  ASSERT_TRUE(wallet0.multisig(&ready, &threshold, &total));
  ASSERT_TRUE(ready);
  ASSERT_TRUE(threshold == M);
  ASSERT_TRUE(total == 2);
  ASSERT_TRUE(wallet1.multisig(&ready, &threshold, &total));
  ASSERT_TRUE(ready);
  ASSERT_TRUE(threshold == M);
  ASSERT_TRUE(total == 2);
}

static void make_M_3_wallet(tools::wallet2 &wallet0, tools::wallet2 &wallet1, tools::wallet2 &wallet2, unsigned int M)
{
  ASSERT_TRUE(M <= 3);

  make_wallet(0, wallet0);
  make_wallet(1, wallet1);
  make_wallet(2, wallet2);

  std::vector<crypto::secret_key> sk0(2), sk1(2), sk2(2);
  std::vector<crypto::public_key> pk0(2), pk1(2), pk2(2);

  std::string mi0 = wallet0.get_multisig_info();
  std::string mi1 = wallet1.get_multisig_info();
  std::string mi2 = wallet2.get_multisig_info();

  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi1, sk0[0], pk0[0]));
  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi2, sk0[1], pk0[1]));
  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi0, sk1[0], pk1[0]));
  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi2, sk1[1], pk1[1]));
  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi0, sk2[0], pk2[0]));
  ASSERT_TRUE(tools::wallet2::verify_multisig_info(mi1, sk2[1], pk2[1]));

  ASSERT_FALSE(wallet0.multisig() || wallet1.multisig() || wallet2.multisig());
  std::string mxi0 = wallet0.make_multisig("", sk0, pk0, M);
  std::string mxi1 = wallet1.make_multisig("", sk1, pk1, M);
  std::string mxi2 = wallet2.make_multisig("", sk2, pk2, M);

  const size_t nset = !mxi0.empty() + !mxi1.empty() + !mxi2.empty();
  ASSERT_TRUE((M < 3 && nset == 3) || (M == 3 && nset == 0));

  if (nset > 0)
  {
    std::unordered_set<crypto::public_key> pkeys;
    std::vector<crypto::public_key> signers(3, crypto::null_pkey);
    ASSERT_TRUE(tools::wallet2::verify_extra_multisig_info(mxi0, pkeys, signers[0]));
    ASSERT_TRUE(tools::wallet2::verify_extra_multisig_info(mxi1, pkeys, signers[1]));
    ASSERT_TRUE(tools::wallet2::verify_extra_multisig_info(mxi2, pkeys, signers[2]));
    ASSERT_TRUE(pkeys.size() == 3);
    ASSERT_TRUE(wallet0.finalize_multisig("", pkeys, signers));
    ASSERT_TRUE(wallet1.finalize_multisig("", pkeys, signers));
    ASSERT_TRUE(wallet2.finalize_multisig("", pkeys, signers));
  }

  ASSERT_TRUE(wallet0.get_account().get_public_address_str(true) == wallet1.get_account().get_public_address_str(true));
  ASSERT_TRUE(wallet0.get_account().get_public_address_str(true) == wallet2.get_account().get_public_address_str(true));

  bool ready;
  uint32_t threshold, total;
  ASSERT_TRUE(wallet0.multisig(&ready, &threshold, &total));
  ASSERT_TRUE(ready);
  ASSERT_TRUE(threshold == M);
  ASSERT_TRUE(total == 3);
  ASSERT_TRUE(wallet1.multisig(&ready, &threshold, &total));
  ASSERT_TRUE(ready);
  ASSERT_TRUE(threshold == M);
  ASSERT_TRUE(total == 3);
  ASSERT_TRUE(wallet2.multisig(&ready, &threshold, &total));
  ASSERT_TRUE(ready);
  ASSERT_TRUE(threshold == M);
  ASSERT_TRUE(total == 3);
}

TEST(multisig, make_2_2)
{
  tools::wallet2 wallet0, wallet1;
  make_M_2_wallet(wallet0, wallet1, 2);
}

TEST(multisig, make_3_3)
{
  tools::wallet2 wallet0, wallet1, wallet2;
  make_M_3_wallet(wallet0, wallet1, wallet2, 3);
}

TEST(multisig, make_2_3)
{
  tools::wallet2 wallet0, wallet1, wallet2;
  make_M_3_wallet(wallet0, wallet1, wallet2, 2);
}
