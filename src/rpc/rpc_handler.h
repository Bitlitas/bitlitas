// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <string>

namespace cryptonote
{

namespace rpc
{


class RpcHandler
{
  public:

    virtual std::string handle(const std::string& request) = 0;

    RpcHandler() { }

    virtual ~RpcHandler() { }
};


}  // rpc

}  // cryptonote
