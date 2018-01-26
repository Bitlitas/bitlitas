// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

extern "C" {
#include "crypto/crypto-ops.h"
}

void sc_reduce32copy(unsigned char * scopy, const unsigned char *s);
