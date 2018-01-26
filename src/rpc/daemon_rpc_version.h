// Copyright (c) 2016-2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

namespace cryptonote
{

namespace rpc
{

static const uint32_t DAEMON_RPC_VERSION_ZMQ_MINOR = 0;
static const uint32_t DAEMON_RPC_VERSION_ZMQ_MAJOR = 1;

static const uint32_t DAEMON_RPC_VERSION_ZMQ = DAEMON_RPC_VERSION_ZMQ_MINOR + (DAEMON_RPC_VERSION_ZMQ_MAJOR << 16);

}  // namespace rpc

}  // namespace cryptonote
