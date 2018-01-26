// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <fstream>

#include "include_base_utils.h"
#include "account.h"
#include "warnings.h"
#include "crypto/crypto.h"
extern "C"
{
#include "crypto/keccak.h"
}
#include "cryptonote_basic_impl.h"
#include "cryptonote_format_utils.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "account"

using namespace std;

DISABLE_VS_WARNINGS(4244 4345)

  namespace cryptonote
{
  //-----------------------------------------------------------------
  account_base::account_base()
  {
    set_null();
  }
  //-----------------------------------------------------------------
  void account_base::set_null()
  {
    m_keys = account_keys();
  }
  //-----------------------------------------------------------------
  void account_base::forget_spend_key()
  {
    m_keys.m_spend_secret_key = crypto::secret_key();
    m_keys.m_multisig_keys.clear();
  }
  //-----------------------------------------------------------------
  crypto::secret_key account_base::generate(const crypto::secret_key& recovery_key, bool recover, bool two_random)
  {
    crypto::secret_key first = generate_keys(m_keys.m_account_address.m_spend_public_key, m_keys.m_spend_secret_key, recovery_key, recover);

    // rng for generating second set of keys is hash of first rng.  means only one set of electrum-style words needed for recovery
    crypto::secret_key second;
    keccak((uint8_t *)&m_keys.m_spend_secret_key, sizeof(crypto::secret_key), (uint8_t *)&second, sizeof(crypto::secret_key));

    generate_keys(m_keys.m_account_address.m_view_public_key, m_keys.m_view_secret_key, second, two_random ? false : true);

    struct tm timestamp = {0};
    timestamp.tm_year = 2014 - 1900;  // year 2014
    timestamp.tm_mon = 6 - 1;  // month june
    timestamp.tm_mday = 8;  // 8th of june
    timestamp.tm_hour = 0;
    timestamp.tm_min = 0;
    timestamp.tm_sec = 0;

    if (recover)
    {
      m_creation_timestamp = mktime(&timestamp);
      if (m_creation_timestamp == (uint64_t)-1) // failure
        m_creation_timestamp = 0; // lowest value
    }
    else
    {
      m_creation_timestamp = time(NULL);
    }
    return first;
  }
  //-----------------------------------------------------------------
  void account_base::create_from_keys(const cryptonote::account_public_address& address, const crypto::secret_key& spendkey, const crypto::secret_key& viewkey)
  {
    m_keys.m_account_address = address;
    m_keys.m_spend_secret_key = spendkey;
    m_keys.m_view_secret_key = viewkey;

    struct tm timestamp = {0};
    timestamp.tm_year = 2014 - 1900;  // year 2014
    timestamp.tm_mon = 4 - 1;  // month april
    timestamp.tm_mday = 15;  // 15th of april
    timestamp.tm_hour = 0;
    timestamp.tm_min = 0;
    timestamp.tm_sec = 0;

    m_creation_timestamp = mktime(&timestamp);
    if (m_creation_timestamp == (uint64_t)-1) // failure
      m_creation_timestamp = 0; // lowest value
  }
  //-----------------------------------------------------------------
  void account_base::create_from_viewkey(const cryptonote::account_public_address& address, const crypto::secret_key& viewkey)
  {
    crypto::secret_key fake;
    memset(&fake, 0, sizeof(fake));
    create_from_keys(address, fake, viewkey);
  }
  //-----------------------------------------------------------------
  bool account_base::make_multisig(const crypto::secret_key &view_secret_key, const crypto::secret_key &spend_secret_key, const crypto::public_key &spend_public_key, const std::vector<crypto::secret_key> &multisig_keys)
  {
    m_keys.m_account_address.m_spend_public_key = spend_public_key;
    m_keys.m_view_secret_key = view_secret_key;
    m_keys.m_spend_secret_key = spend_secret_key;
    m_keys.m_multisig_keys = multisig_keys;
    return crypto::secret_key_to_public_key(view_secret_key, m_keys.m_account_address.m_view_public_key);
  }
  //-----------------------------------------------------------------
  void account_base::finalize_multisig(const crypto::public_key &spend_public_key)
  {
    m_keys.m_account_address.m_spend_public_key = spend_public_key;
  }
  //-----------------------------------------------------------------
  const account_keys& account_base::get_keys() const
  {
    return m_keys;
  }
  //-----------------------------------------------------------------
  std::string account_base::get_public_address_str(bool testnet) const
  {
    //TODO: change this code into base 58
    return get_account_address_as_str(testnet, false, m_keys.m_account_address);
  }
  //-----------------------------------------------------------------
  std::string account_base::get_public_integrated_address_str(const crypto::hash8 &payment_id, bool testnet) const
  {
    //TODO: change this code into base 58
    return get_account_integrated_address_as_str(testnet, m_keys.m_account_address, payment_id);
  }
  //-----------------------------------------------------------------
}
