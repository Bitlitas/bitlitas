// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <stddef.h>
#include <stdint.h>

#include "groestl.h"

void hash_extra_groestl(const void *data, size_t length, char *hash) {
  groestl(data, length * 8, (uint8_t*)hash);
}
