// Copyright (c) 2018, Bitlitas 
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <list>

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::list<T> &v);
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::list<T> &v);

namespace serialization
{
  namespace detail
  {
    template <typename T>
    void do_add(std::list<T> &c, T &&e)
    {
      c.emplace_back(std::move(e));
    }
  }
}

#include "serialization.h"

template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::list<T> &v) { return do_serialize_container(ar, v); }
template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::list<T> &v) { return do_serialize_container(ar, v); }

