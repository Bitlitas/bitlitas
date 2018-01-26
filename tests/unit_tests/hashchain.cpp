// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

// FIXME: move this into a full wallet2 unit test suite, if possible

#include "gtest/gtest.h"

#include "wallet/wallet2.h"

static crypto::hash make_hash(uint64_t n)
{
  union
  {
    crypto::hash hash;
    uint64_t n;
  } hash;
  hash.hash = crypto::null_hash;
  hash.n = n;
  return hash.hash;
}

TEST(hashchain, empty)
{
  tools::hashchain hashchain;
  ASSERT_EQ(hashchain.size(), 0);
  ASSERT_EQ(hashchain.offset(), 0);
}

TEST(hashchain, genesis)
{
  tools::hashchain hashchain;
  hashchain.push_back(make_hash(1));
  ASSERT_EQ(hashchain.size(), 1);
  ASSERT_EQ(hashchain.genesis(), make_hash(1));
  hashchain.push_back(make_hash(2));
  ASSERT_EQ(hashchain.size(), 2);
  ASSERT_EQ(hashchain.genesis(), make_hash(1));
}

TEST(hashchain, push_back)
{
  tools::hashchain hashchain;
  hashchain.push_back(make_hash(1));
  hashchain.push_back(make_hash(2));
  hashchain.push_back(make_hash(3));
  ASSERT_EQ(hashchain[0], make_hash(1));
  ASSERT_EQ(hashchain[1], make_hash(2));
  ASSERT_EQ(hashchain[2], make_hash(3));
}

TEST(hashchain, clear_empty)
{
  tools::hashchain hashchain;
  ASSERT_TRUE(hashchain.empty());
  hashchain.push_back(make_hash(1));
  ASSERT_FALSE(hashchain.empty());
  hashchain.push_back(make_hash(2));
  ASSERT_FALSE(hashchain.empty());
  hashchain.clear();
  ASSERT_TRUE(hashchain.empty());
}

TEST(hashchain, crop)
{
  tools::hashchain hashchain;
  hashchain.push_back(make_hash(1));
  hashchain.push_back(make_hash(2));
  hashchain.push_back(make_hash(3));
  ASSERT_EQ(hashchain.size(), 3);
  ASSERT_EQ(hashchain[0], make_hash(1));
  ASSERT_EQ(hashchain[1], make_hash(2));
  ASSERT_EQ(hashchain[2], make_hash(3));
  hashchain.crop(3);
  ASSERT_EQ(hashchain.size(), 3);
  hashchain.crop(2);
  ASSERT_EQ(hashchain.size(), 2);
  ASSERT_EQ(hashchain[0], make_hash(1));
  ASSERT_EQ(hashchain[1], make_hash(2));
  ASSERT_EQ(hashchain.genesis(), make_hash(1));
  hashchain.crop(0);
  ASSERT_TRUE(hashchain.empty());
  ASSERT_EQ(hashchain.size(), 0);
  hashchain.push_back(make_hash(5));
  ASSERT_EQ(hashchain.genesis(), make_hash(5));
  ASSERT_EQ(hashchain.size(), 1);
}

TEST(hashchain, trim)
{
  tools::hashchain hashchain;
  hashchain.push_back(make_hash(1));
  hashchain.push_back(make_hash(2));
  hashchain.push_back(make_hash(3));
  ASSERT_EQ(hashchain.offset(), 0);
  hashchain.trim(2);
  ASSERT_EQ(hashchain.offset(), 2);
  ASSERT_EQ(hashchain.size(), 3);
  ASSERT_EQ(hashchain[2], make_hash(3));
  hashchain.trim(3);
  ASSERT_EQ(hashchain.offset(), 2); // never gets it empty
  ASSERT_EQ(hashchain.size(), 3);
  ASSERT_FALSE(hashchain.empty());
  ASSERT_EQ(hashchain.genesis(), make_hash(1));
}
