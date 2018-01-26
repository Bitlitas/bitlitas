// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <cstdint>
#include <vector>

#include "crypto/hash.h"

namespace cryptonote
{
    typedef std::uint64_t difficulty_type;

    /**
     * @brief checks if a hash fits the given difficulty
     *
     * The hash passes if (hash * difficulty) < 2^256.
     * Phrased differently, if (hash * difficulty) fits without overflow into
     * the least significant 256 bits of the 320 bit multiplication result.
     *
     * @param hash the hash to check
     * @param difficulty the difficulty to check against
     *
     * @return true if valid, else false
     */
    bool check_hash(const crypto::hash &hash, difficulty_type difficulty);
    difficulty_type next_difficulty(std::vector<std::uint64_t> timestamps, std::vector<difficulty_type> cumulative_difficulties, size_t target_seconds);
}
