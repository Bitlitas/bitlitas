// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "cryptonote_basic.h"
#include "crypto/crypto.h"
#include "serialization/keyvalue_serialization.h"

namespace cryptonote
{

  struct account_keys
  {
    account_public_address m_account_address;
    crypto::secret_key   m_spend_secret_key;
    crypto::secret_key   m_view_secret_key;
    std::vector<crypto::secret_key> m_multisig_keys;

    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(m_account_address)
      KV_SERIALIZE_VAL_POD_AS_BLOB_FORCE(m_spend_secret_key)
      KV_SERIALIZE_VAL_POD_AS_BLOB_FORCE(m_view_secret_key)
      KV_SERIALIZE_CONTAINER_POD_AS_BLOB(m_multisig_keys)
    END_KV_SERIALIZE_MAP()
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  class account_base
  {
  public:
    account_base();
    crypto::secret_key generate(const crypto::secret_key& recovery_key = crypto::secret_key(), bool recover = false, bool two_random = false);
    void create_from_keys(const cryptonote::account_public_address& address, const crypto::secret_key& spendkey, const crypto::secret_key& viewkey);
    void create_from_viewkey(const cryptonote::account_public_address& address, const crypto::secret_key& viewkey);
    bool make_multisig(const crypto::secret_key &view_secret_key, const crypto::secret_key &spend_secret_key, const crypto::public_key &spend_public_key, const std::vector<crypto::secret_key> &multisig_keys);
    void finalize_multisig(const crypto::public_key &spend_public_key);
    const account_keys& get_keys() const;
    std::string get_public_address_str(bool testnet) const;
    std::string get_public_integrated_address_str(const crypto::hash8 &payment_id, bool testnet) const;

    uint64_t get_createtime() const { return m_creation_timestamp; }
    void set_createtime(uint64_t val) { m_creation_timestamp = val; }

    bool load(const std::string& file_path);
    bool store(const std::string& file_path);

    void forget_spend_key();
    const std::vector<crypto::secret_key> &get_multisig_keys() const { return m_keys.m_multisig_keys; }

    template <class t_archive>
    inline void serialize(t_archive &a, const unsigned int /*ver*/)
    {
      a & m_keys;
      a & m_creation_timestamp;
    }

    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(m_keys)
      KV_SERIALIZE(m_creation_timestamp)
    END_KV_SERIALIZE_MAP()

  private:
    void set_null();
    account_keys m_keys;
    uint64_t m_creation_timestamp;
  };
}
