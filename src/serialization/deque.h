// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <deque>

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::deque<T> &v);
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::deque<T> &v);

namespace serialization
{
  namespace detail
  {
    template <typename T>
    void do_reserve(std::deque<T> &c, size_t N)
    {
      c.reserve(N);
    }

    template <typename T>
    void do_add(std::deque<T> &c, T &&e)
    {
      c.emplace_back(std::move(e));
    }
  }
}

#include "serialization.h"

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::deque<T> &v) { return do_serialize_container(ar, v); }
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::deque<T> &v) { return do_serialize_container(ar, v); }

