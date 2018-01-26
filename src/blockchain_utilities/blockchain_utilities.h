// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "version.h"

// bounds checking is done before writing to buffer, but buffer size
// should be a sensible maximum
#define BUFFER_SIZE 1000000
#define CHUNK_SIZE_WARNING_THRESHOLD 500000
#define NUM_BLOCKS_PER_CHUNK 1
#define BLOCKCHAIN_RAW "blockchain.raw"

