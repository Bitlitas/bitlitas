// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

// FIXME: Why is this ifdef needed?  Hopefully making it struct won't break things.

/*
#if defined(_MSC_VER)
#define POD_CLASS struct
#else
#define POD_CLASS class
#endif
*/

#define POD_CLASS struct
