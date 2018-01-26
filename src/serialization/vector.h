// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <vector>
#include "serialization.h"

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::vector<T> &v);
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::vector<T> &v);

namespace serialization
{
  namespace detail
  {
    template <typename T>
    void do_reserve(std::vector<T> &c, size_t N)
    {
      c.reserve(N);
    }

    template <typename T>
    void do_add(std::vector<T> &c, T &&e)
    {
      c.emplace_back(std::move(e));
    }
  }
}

#include "container.h"

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::vector<T> &v) { return do_serialize_container(ar, v); }
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::vector<T> &v) { return do_serialize_container(ar, v); }

