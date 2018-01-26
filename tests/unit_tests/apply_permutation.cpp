// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"
#include "common/apply_permutation.h"

TEST(apply_permutation, empty)
{
  std::vector<int> v = {};
  tools::apply_permutation({}, v);
  ASSERT_EQ(v, std::vector<int>({}));
}

TEST(apply_permutation, reorder)
{
  //                    0  1  2  3  4  5  6
  std::vector<int> v = {8, 4, 6, 1, 7, 2, 4};
  tools::apply_permutation({3, 5, 6, 1, 2, 4, 0}, v);
  ASSERT_EQ(v, std::vector<int>({1, 2, 4, 4, 6, 7, 8}));
}

TEST(apply_permutation, bad_size)
{
  std::vector<int> v_large = {8, 4, 6, 1, 7, 2, 4, 9};
  std::vector<int> v_small = {8, 4, 6, 1, 7, 2};
  try
  { 
    tools::apply_permutation({3, 5, 6, 1, 2, 4, 0}, v_large);
    ASSERT_FALSE(true);
  }
  catch (const std::exception &e) {}
  try
  { 
    tools::apply_permutation({3, 5, 6, 1, 2, 4, 0}, v_small);
    ASSERT_FALSE(true);
  }
  catch (const std::exception &e) {}
}

TEST(apply_permutation, bad_permutation)
{
  std::vector<int> v = {8, 4, 6, 1, 7, 2, 4};
  try
  { 
    tools::apply_permutation({3, 5, 6, 1, 2, 4, 1}, v);
    ASSERT_FALSE(true);
  }
  catch (const std::exception &e) {}
}
