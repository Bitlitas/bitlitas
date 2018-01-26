// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <set>

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::unordered_set<T> &v);
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::unordered_set<T> &v);

namespace serialization
{
  namespace detail
  {
    template <typename T>
    void do_add(std::unordered_set<T> &c, T &&e)
    {
      c.insert(std::move(e));
    }
  }
}

#include "serialization.h"

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::unordered_set<T> &v) { return do_serialize_container(ar, v); }
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::unordered_set<T> &v) { return do_serialize_container(ar, v); }

