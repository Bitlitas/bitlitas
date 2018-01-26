// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <stddef.h>
#include <stdint.h>

#include "blake256.h"

void hash_extra_blake(const void *data, size_t length, char *hash) {
  blake256_hash((uint8_t*)hash, data, length);
}
