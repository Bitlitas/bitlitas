// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "zmq_server.h"
#include <boost/chrono/chrono.hpp>

namespace cryptonote
{

namespace rpc
{

ZmqServer::ZmqServer(RpcHandler& h) :
    handler(h),
    stop_signal(false),
    running(false),
    context(DEFAULT_NUM_ZMQ_THREADS) // TODO: make this configurable
{
}

ZmqServer::~ZmqServer()
{
}

void ZmqServer::serve()
{

  while (1)
  {
    try
    {
      zmq::message_t message;

      if (!rep_socket)
      {
        throw std::runtime_error("ZMQ RPC server reply socket is null");
      }
      while (rep_socket->recv(&message))
      {
        std::string message_string(reinterpret_cast<const char *>(message.data()), message.size());

        MDEBUG(std::string("Received RPC request: \"") + message_string + "\"");

        std::string response = handler.handle(message_string);

        zmq::message_t reply(response.size());
        memcpy((void *) reply.data(), response.c_str(), response.size());

        rep_socket->send(reply);
        MDEBUG(std::string("Sent RPC reply: \"") + response + "\"");

      }
    }
    catch (const boost::thread_interrupted& e)
    {
      MDEBUG("ZMQ Server thread interrupted.");
    }
    catch (const zmq::error_t& e)
    {
      MERROR(std::string("ZMQ error: ") + e.what());
    }
    boost::this_thread::interruption_point();
  }
}

bool ZmqServer::addIPCSocket(std::string address, std::string port)
{
  MERROR("ZmqServer::addIPCSocket not yet implemented!");
  return false;
}

bool ZmqServer::addTCPSocket(std::string address, std::string port)
{
  try
  {
    std::string addr_prefix("tcp://");

    rep_socket.reset(new zmq::socket_t(context, ZMQ_REP));

    rep_socket->setsockopt(ZMQ_RCVTIMEO, DEFAULT_RPC_RECV_TIMEOUT_MS);

    std::string bind_address = addr_prefix + address + std::string(":") + port;
    rep_socket->bind(bind_address.c_str());
  }
  catch (const std::exception& e)
  {
    MERROR(std::string("Error creating ZMQ Socket: ") + e.what());
    return false;
  }
  return true;
}

void ZmqServer::run()
{
  running = true;
  run_thread = boost::thread(boost::bind(&ZmqServer::serve, this));
}

void ZmqServer::stop()
{
  if (!running) return;

  stop_signal = true;

  run_thread.interrupt();
  run_thread.join();

  running = false;

  return;
}


}  // namespace cryptonote

}  // namespace rpc
