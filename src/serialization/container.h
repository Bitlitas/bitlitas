// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "serialization.h"

namespace serialization
{
  namespace detail
  {
    template <typename Archive, class T>
    bool serialize_container_element(Archive& ar, T& e)
    {
      return ::do_serialize(ar, e);
    }

    template <typename Archive>
    bool serialize_container_element(Archive& ar, uint32_t& e)
    {
      ar.serialize_varint(e);
      return true;
    }

    template <typename Archive>
    bool serialize_container_element(Archive& ar, uint64_t& e)
    {
      ar.serialize_varint(e);
      return true;
    }

    template <typename C>
    void do_reserve(C &c, size_t N) {}
  }
}

template <template <bool> class Archive, typename C>
bool do_serialize_container(Archive<false> &ar, C &v)
{
  size_t cnt;
  ar.begin_array(cnt);
  if (!ar.stream().good())
    return false;
  v.clear();

  // very basic sanity check
  if (ar.remaining_bytes() < cnt) {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }

  ::serialization::detail::do_reserve(v, cnt);

  for (size_t i = 0; i < cnt; i++) {
    if (i > 0)
      ar.delimit_array();
    typename C::value_type e;
    if (!::serialization::detail::serialize_container_element(ar, e))
      return false;
    ::serialization::detail::do_add(v, std::move(e));
    if (!ar.stream().good())
      return false;
  }
  ar.end_array();
  return true;
}

template <template <bool> class Archive, typename C>
bool do_serialize_container(Archive<true> &ar, C &v)
{
  size_t cnt = v.size();
  ar.begin_array(cnt);
  for (auto i = v.begin(); i != v.end(); ++i)
  {
    if (!ar.stream().good())
      return false;
    if (i != v.begin())
      ar.delimit_array();
    if(!::serialization::detail::serialize_container_element(ar, const_cast<typename C::value_type&>(*i)))
      return false;
    if (!ar.stream().good())
      return false;
  }
  ar.end_array();
  return true;
}
