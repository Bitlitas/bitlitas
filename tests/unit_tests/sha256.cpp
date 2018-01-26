// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"

#include "common/util.h"
#include "string_tools.h"

static bool check(const std::string &data, const char *expected_hash_hex)
{
  crypto::hash hash, expected_hash;
  if (!epee::string_tools::hex_to_pod(expected_hash_hex, expected_hash))
    return false;
  return tools::sha256sum((const uint8_t*)data.data(), data.size(), hash) && hash == expected_hash;
}

TEST(sha256, empty) { ASSERT_TRUE(check(std::string(), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")); }
TEST(sha256, small) { ASSERT_TRUE(check("0123456789", "84d89877f0d4041efb6bf91a16f0248f2fd573e6af05c19f96bedb9f882f7882")); }
TEST(sha256, large) { ASSERT_TRUE(check(std::string(65536*256, 0), "080acf35a507ac9849cfcba47dc2ad83e01b75663a516279c8b9d243b719643e")); }

