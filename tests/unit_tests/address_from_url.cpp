// Copyright (c) 2018, Bitlitas 
// All rights reserved. Based on Cryptonote and Monero.

// FIXME: move this into a full wallet2 unit test suite, if possible

#include "gtest/gtest.h"

#include "wallet/wallet2.h"
#include "common/dns_utils.h"
#include "simplewallet/simplewallet.h"
#include <string>

TEST(AddressFromTXT, Success)
{
  std::string addr = "46BeWrHpwXmHDpDEUmZBWZfoQpdc6HaERCNmx1pEYL2rAcuwufPN9rXHHtyUA4QVy66qeFQkn6sfK8aHYjA3jk3o1Bv16em";

  std::string txtr = "oa1:xmr";
  txtr += " recipient_address=";
  txtr += addr;
  txtr += ";";

  std::string res = tools::dns_utils::address_from_txt_record(txtr);

  EXPECT_STREQ(addr.c_str(), res.c_str());

  std::string txtr2 = "foobar";

  txtr2 += txtr;

  txtr2 += "more foobar";

  res = tools::dns_utils::address_from_txt_record(txtr2);

  EXPECT_STREQ(addr.c_str(), res.c_str());

  std::string txtr3 = "foobar oa1:xmr tx_description=\"Donation for Bitlitas Development Fund\"; ";
  txtr3 += "recipient_address=";
  txtr3 += addr;
  txtr3 += "; foobar";

  res = tools::dns_utils::address_from_txt_record(txtr3);

  EXPECT_STREQ(addr.c_str(), res.c_str());
}

TEST(AddressFromTXT, Failure)
{
  std::string txtr = "oa1:xmr recipient_address=not a real address";

  std::string res = tools::dns_utils::address_from_txt_record(txtr);

  ASSERT_STREQ("", res.c_str());

  txtr += ";";

  res = tools::dns_utils::address_from_txt_record(txtr);
  ASSERT_STREQ("", res.c_str());
}

TEST(AddressFromURL, Success)
{
  const std::string addr = BITLITAS_DONATION_ADDR;
  
  bool dnssec_result = false;

  std::vector<std::string> addresses = tools::dns_utils::addresses_from_url("donate.bitlitas.lt", dnssec_result);

  EXPECT_EQ(1, addresses.size());
  if (addresses.size() == 1)
  {
    EXPECT_STREQ(addr.c_str(), addresses[0].c_str());
  }

  // OpenAlias address with an @ instead of first .
  addresses = tools::dns_utils::addresses_from_url("donate@bitlitas.lt", dnssec_result);
  EXPECT_EQ(1, addresses.size());
  if (addresses.size() == 1)
  {
    EXPECT_STREQ(addr.c_str(), addresses[0].c_str());
  }
}

TEST(AddressFromURL, Failure)
{
  bool dnssec_result = false;

  std::vector<std::string> addresses = tools::dns_utils::addresses_from_url("example.invalid", dnssec_result);

  // for a non-existing domain such as "example.invalid", the non-existence is proved with NSEC records
  ASSERT_TRUE(dnssec_result);

  ASSERT_EQ(0, addresses.size());
}
