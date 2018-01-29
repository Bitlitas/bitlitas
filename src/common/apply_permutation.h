// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

// Most of this file is originally copyright (c) 2017 Raymond Chen, Microsoft
// This algorithm is adapted from Raymond Chen's code:
// https://blogs.msdn.microsoft.com/oldnewthing/20170109-00/?p=95145

#pragma once

#include <vector>
#include <functional>
#include "misc_log_ex.h"

namespace tools
{

template<typename F>
void apply_permutation(std::vector<size_t> permutation, const F &swap)
{
  //sanity check
  for (size_t n = 0; n < permutation.size(); ++n)
    CHECK_AND_ASSERT_THROW_MES(std::find(permutation.begin(), permutation.end(), n) != permutation.end(), "Bad permutation");

  for (size_t i = 0; i < permutation.size(); ++i)
  {
    size_t current = i;
    while (i != permutation[current])
    {
      size_t next = permutation[current];
      swap(current, next);
      permutation[current] = current;
      current = next;
    }
    permutation[current] = current;
  }
}

template<typename T>
void apply_permutation(const std::vector<size_t> &permutation, std::vector<T> &v)
{
  CHECK_AND_ASSERT_THROW_MES(permutation.size() == v.size(), "Mismatched vector sizes");
  apply_permutation(permutation, [&v](size_t i0, size_t i1){ std::swap(v[i0], v[i1]); });
}

}
