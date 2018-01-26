// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.
// Adapted from Java code by Sarang Noether

#pragma once

#ifndef BULLETPROOFS_H
#define BULLETPROOFS_H

#include "rctTypes.h"

namespace rct
{

Bulletproof bulletproof_PROVE(const rct::key &v, const rct::key &gamma);
Bulletproof bulletproof_PROVE(uint64_t v, const rct::key &gamma);
bool bulletproof_VERIFY(const Bulletproof &proof);

}

#endif
