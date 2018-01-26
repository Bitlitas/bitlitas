// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#if defined(__cplusplus)
#include "crypto/crypto.h"

extern "C" {
#endif

void setup_random(void);

#if defined(__cplusplus)
}

bool check_scalar(const crypto::ec_scalar &scalar);
void random_scalar(crypto::ec_scalar &res);
void hash_to_scalar(const void *data, std::size_t length, crypto::ec_scalar &res);
void hash_to_point(const crypto::hash &h, crypto::ec_point &res);
void hash_to_ec(const crypto::public_key &key, crypto::ec_point &res);
#endif
