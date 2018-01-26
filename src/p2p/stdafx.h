// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "targetver.h"


#if !defined(__GNUC__) 
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif 



#include <stdio.h>


#define BOOST_FILESYSTEM_VERSION 3
#define ENABLE_RELEASE_LOGGING
#include "log_opt_defs.h"
#include "misc_log_ex.h"



