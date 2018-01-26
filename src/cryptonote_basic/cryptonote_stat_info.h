// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once
#include "serialization/keyvalue_serialization.h"

namespace cryptonote
{
  struct core_stat_info
  {
    uint64_t tx_pool_size;
    uint64_t blockchain_height;
    uint64_t mining_speed;
    uint64_t alternative_blocks;
    std::string top_block_id_str;
    
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(tx_pool_size)
      KV_SERIALIZE(blockchain_height)
      KV_SERIALIZE(mining_speed)
      KV_SERIALIZE(alternative_blocks)
      KV_SERIALIZE(top_block_id_str)
    END_KV_SERIALIZE_MAP()
  };
}
