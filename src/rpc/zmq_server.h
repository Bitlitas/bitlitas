// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/thread/thread.hpp>
#include <zmq.hpp>
#include <string>
#include <memory>

#include "common/command_line.h"

#include "rpc_handler.h"

namespace cryptonote
{

namespace rpc
{

static constexpr int DEFAULT_NUM_ZMQ_THREADS = 1;
static constexpr int DEFAULT_RPC_RECV_TIMEOUT_MS = 1000;

class ZmqServer
{
  public:

    ZmqServer(RpcHandler& h);

    ~ZmqServer();

    static void init_options(boost::program_options::options_description& desc);

    void serve();

    bool addIPCSocket(std::string address, std::string port);
    bool addTCPSocket(std::string address, std::string port);

    void run();
    void stop();

  private:
    RpcHandler& handler;

    volatile bool stop_signal;
    volatile bool running;

    zmq::context_t context;

    boost::thread run_thread;

    std::unique_ptr<zmq::socket_t> rep_socket;
};


}  // namespace cryptonote

}  // namespace rpc
