// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "serialization/keyvalue_serialization.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <ostream>

namespace cryptonote
{
  struct subaddress_index
  {
    uint32_t major;
    uint32_t minor;
    bool operator==(const subaddress_index& rhs) const { return !memcmp(this, &rhs, sizeof(subaddress_index)); }
    bool operator!=(const subaddress_index& rhs) const { return !(*this == rhs); }
    bool is_zero() const { return major == 0 && minor == 0; }

    BEGIN_SERIALIZE_OBJECT()
      FIELD(major)
      FIELD(minor)
    END_SERIALIZE()

    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(major)
      KV_SERIALIZE(minor)
    END_KV_SERIALIZE_MAP()
  };
}

namespace cryptonote {
  inline std::ostream& operator<<(std::ostream& out, const cryptonote::subaddress_index& subaddr_index)
  {
    return out << subaddr_index.major << '/' << subaddr_index.minor;
  }
}

namespace std
{
  template <>
  struct hash<cryptonote::subaddress_index>
  {
    size_t operator()(const cryptonote::subaddress_index& index ) const
    {
      size_t res;
      if (sizeof(size_t) == 8)
      {
        res = ((uint64_t)index.major << 32) | index.minor;
      }
      else
      {
        // https://stackoverflow.com/a/17017281
        res = 17;
        res = res * 31 + hash<uint32_t>()(index.major);
        res = res * 31 + hash<uint32_t>()(index.minor);
      }
      return res;
    }
  };
}

BOOST_CLASS_VERSION(cryptonote::subaddress_index, 0)

namespace boost
{
  namespace serialization
  {
    template <class Archive>
    inline void serialize(Archive &a, cryptonote::subaddress_index &x, const boost::serialization::version_type ver)
    {
      a & x.major;
      a & x.minor;
    }
  }
}
