// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "account.h"
#include "cryptonote_boost_serialization.h"

//namespace cryptonote {
namespace boost
{
  namespace serialization
  {
    template <class Archive>
    inline void serialize(Archive &a, cryptonote::account_keys &x, const boost::serialization::version_type ver)
    {
      a & x.m_account_address;
      a & x.m_spend_secret_key;
      a & x.m_view_secret_key;
    }

    template <class Archive>
    inline void serialize(Archive &a, cryptonote::account_public_address &x, const boost::serialization::version_type ver)
    {
      a & x.m_spend_public_key;
      a & x.m_view_public_key;
    }

  }
}
