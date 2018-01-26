// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"

#ifdef STATICLIB

extern "C" int dnskey_algo_id_is_supported(int);

TEST(unbound, supported_algorithms)
{
  // Bitlitas causes these to be tried, but we don't have access
  // to this internal unbound header here, so we use raw numbers
  // LDNS_RSASHA1            = 5,
  // LDNS_RSASHA1_NSEC3      = 7,
  // LDNS_RSASHA256          = 8,   /* RFC 5702 */
  // LDNS_ECDSAP256SHA256    = 13,  /* RFC 6605 */

  ASSERT_TRUE(dnskey_algo_id_is_supported(5));
  ASSERT_TRUE(dnskey_algo_id_is_supported(7));
  ASSERT_TRUE(dnskey_algo_id_is_supported(8));
  ASSERT_TRUE(dnskey_algo_id_is_supported(13));
}

#endif

