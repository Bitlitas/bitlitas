// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "common/dns_utils.h"

TEST(DNSResolver, IPv4Success)
{
  tools::DNSResolver resolver = tools::DNSResolver::create();

  bool avail, valid;

  auto ips = resolver.get_ipv4("example.com", avail, valid);

  ASSERT_EQ(1, ips.size());

  //ASSERT_STREQ("93.184.216.119", ips[0].c_str());

  ips = tools::DNSResolver::instance().get_ipv4("example.com", avail, valid);

  ASSERT_EQ(1, ips.size());

  //ASSERT_STREQ("93.184.216.119", ips[0].c_str());
}

TEST(DNSResolver, IPv4Failure)
{
  // guaranteed by IANA/ICANN/RFC to be invalid
  tools::DNSResolver resolver = tools::DNSResolver::create();

  bool avail, valid;

  auto ips = resolver.get_ipv4("example.invalid", avail, valid);

  ASSERT_EQ(0, ips.size());

  ips = tools::DNSResolver::instance().get_ipv4("example.invalid", avail, valid);

  ASSERT_EQ(0, ips.size());
}

TEST(DNSResolver, DNSSECSuccess)
{
  tools::DNSResolver resolver = tools::DNSResolver::create();

  bool avail, valid;

  auto ips = resolver.get_ipv4("example.com", avail, valid);

  ASSERT_EQ(1, ips.size());

  //ASSERT_STREQ("93.184.216.119", ips[0].c_str());

  ASSERT_TRUE(avail);
  ASSERT_TRUE(valid);
}

TEST(DNSResolver, DNSSECFailure)
{
  tools::DNSResolver resolver = tools::DNSResolver::create();

  bool avail, valid;

  auto ips = resolver.get_ipv4("dnssec-failed.org", avail, valid);

  ASSERT_EQ(1, ips.size());

  //ASSERT_STREQ("93.184.216.119", ips[0].c_str());

  ASSERT_TRUE(avail);
  ASSERT_FALSE(valid);
}

// It would be great to include an IPv6 test and assume it'll pass, but not every ISP / resolver plays nicely with IPv6;)
/*TEST(DNSResolver, IPv6Success)
{
  tools::DNSResolver resolver = tools::DNSResolver::create();

  bool avail, valid;

  auto ips = resolver.get_ipv6("example.com", avail, valid);

  ASSERT_EQ(1, ips.size());

  ASSERT_STREQ("2606:2800:220:6d:26bf:1447:1097:aa7", ips[0].c_str());

  ips = tools::DNSResolver::instance().get_ipv6("example.com", avail, valid);

  ASSERT_EQ(1, ips.size());

  ASSERT_STREQ("2606:2800:220:6d:26bf:1447:1097:aa7", ips[0].c_str());
}*/

TEST(DNSResolver, IPv6Failure)
{
  // guaranteed by IANA/ICANN/RFC to be invalid
  tools::DNSResolver resolver = tools::DNSResolver::create();

  bool avail, valid;

  auto ips = resolver.get_ipv6("example.invalid", avail, valid);

  ASSERT_EQ(0, ips.size());

  ips = tools::DNSResolver::instance().get_ipv6("example.invalid", avail, valid);

  ASSERT_EQ(0, ips.size());
}

TEST(DNSResolver, GetTXTRecord)
{
  bool avail, valid;

  std::vector<std::string> records = tools::DNSResolver::instance().get_txt_record("donate.bitlitas.lt", avail, valid);

  EXPECT_NE(0, records.size());

  for (auto& rec : records)
  {
    std::cout << "TXT record for donate.bitlitas.lt: " << rec << std::endl;
  }

  // replace first @ with .
  std::string addr = tools::DNSResolver::instance().get_dns_format_from_oa_address("donate@bitlitas.lt");
  EXPECT_STREQ("donate.bitlitas.lt", addr.c_str());

  // no change
  addr = tools::DNSResolver::instance().get_dns_format_from_oa_address("donate.bitlitas.lt");
  EXPECT_STREQ("donate.bitlitas.lt", addr.c_str());
}

TEST(DNS_PUBLIC, empty) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("").c_str()); }
TEST(DNS_PUBLIC, default) { EXPECT_STREQ("8.8.4.4", tools::dns_utils::parse_dns_public("tcp").c_str()); }
TEST(DNS_PUBLIC, invalid_scheme) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("invalid").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_alpha) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://invalid").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_num1) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_num3) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3.4.5").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_num4_extra) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3.4.5.6x").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_num4_range) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3.4.542.6").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_dot) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3.4.5.6.").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_num5) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3.4.5.6.7").c_str()); }
TEST(DNS_PUBLIC, invalid_ip_4_missing) { EXPECT_STREQ("", tools::dns_utils::parse_dns_public("tcp://3.4..7").c_str()); }
TEST(DNS_PUBLIC, valid_ip_lo) { EXPECT_STREQ("127.0.0.1", tools::dns_utils::parse_dns_public("tcp://127.0.0.1").c_str()); }
TEST(DNS_PUBLIC, valid_ip) { EXPECT_STREQ("3.4.5.6", tools::dns_utils::parse_dns_public("tcp://3.4.5.6").c_str()); }
