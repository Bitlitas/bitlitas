// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once
#include <memory>
#include "serialization.h"

namespace serialization
{
  namespace detail
  {
    template <typename Archive, class T>
    bool serialize_pair_element(Archive& ar, T& e)
    {
      return ::do_serialize(ar, e);
    }

    template <typename Archive>
    bool serialize_pair_element(Archive& ar, uint64_t& e)
    {
      ar.serialize_varint(e);
      return true;
    }
  }
}

template <template <bool> class Archive, class F, class S>
inline bool do_serialize(Archive<false>& ar, std::pair<F,S>& p)
{
  size_t cnt;
  ar.begin_array(cnt);
  if (!ar.stream().good())
    return false;
  if (cnt != 2)
    return false;

  if (!::serialization::detail::serialize_pair_element(ar, p.first))
    return false;
  if (!ar.stream().good())
    return false;
  ar.delimit_array();
  if (!::serialization::detail::serialize_pair_element(ar, p.second))
    return false;
  if (!ar.stream().good())
    return false;

  ar.end_array();
  return true;
}

template <template <bool> class Archive, class F, class S>
inline bool do_serialize(Archive<true>& ar, std::pair<F,S>& p)
{
  ar.begin_array(2);
  if (!ar.stream().good())
    return false;
  if(!::serialization::detail::serialize_pair_element(ar, p.first))
    return false;
  if (!ar.stream().good())
    return false;
  ar.delimit_array();
  if(!::serialization::detail::serialize_pair_element(ar, p.second))
    return false;
  if (!ar.stream().good())
    return false;
  ar.end_array();
  return true;
}

