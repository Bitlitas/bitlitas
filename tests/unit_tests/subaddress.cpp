// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <boost/filesystem.hpp>
#include "gtest/gtest.h"

#include "include_base_utils.h"
#include "wallet/wallet2.h"
#include "crypto/crypto.h"
#include "cryptonote_basic/account.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "wallet/api/subaddress.h"

class WalletSubaddress : public ::testing::Test 
{
  protected:
    virtual void SetUp() 
    {
      try
      {
        w1.generate("", password, recovery_key, true, false);
      }
      catch (const std::exception& e)
      {
        LOG_ERROR("failed to generate wallet: " << e.what());
        throw e;
      }

      w1.add_subaddress_account(test_label);
      w1.set_subaddress_label(subaddress_index, test_label);
    }

    virtual void TearDown()
    {
    }

    tools::wallet2 w1;
    const std::string password = "testpass";
    crypto::secret_key recovery_key = crypto::secret_key();
    const std::string test_label = "subaddress test label";

    uint32_t major_index = 0;
    uint32_t minor_index = 0;
    const cryptonote::subaddress_index subaddress_index = {major_index, minor_index};
};

TEST_F(WalletSubaddress, GetSubaddressLabel)
{
  EXPECT_EQ(test_label, w1.get_subaddress_label(subaddress_index));
}

TEST_F(WalletSubaddress, AddSubaddress)
{
  std::string label = "test adding subaddress";
  w1.add_subaddress(0, label);
  EXPECT_EQ(label, w1.get_subaddress_label({0, 1}));
}

TEST_F(WalletSubaddress, OutOfBoundsIndexes)
{
  try 
  {
    w1.get_subaddress_label({1,0});
  } 
  catch(const std::exception& e)
  {
    EXPECT_STREQ("index_major is out of bound", e.what());  
  }   
  try 
  {
    w1.get_subaddress_label({0,2});
  } 
  catch(const std::exception& e)
  {
    EXPECT_STREQ("index.minor is out of bound", e.what());  
  }   
}
