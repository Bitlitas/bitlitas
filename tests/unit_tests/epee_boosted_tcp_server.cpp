// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <boost/chrono/chrono.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>

#include "gtest/gtest.h"

#include "include_base_utils.h"
#include "string_tools.h"
#include "net/abstract_tcp_server2.h"

namespace
{
  const uint32_t test_server_port = 5626;
  const std::string test_server_host("127.0.0.1");

  struct test_connection_context : public epee::net_utils::connection_context_base
  {
  };

  struct test_protocol_handler_config
  {
  };

  struct test_protocol_handler
  {
    typedef test_connection_context connection_context;
    typedef test_protocol_handler_config config_type;

    test_protocol_handler(epee::net_utils::i_service_endpoint* /*psnd_hndlr*/, config_type& /*config*/, connection_context& /*conn_context*/)
    {
    }

    void after_init_connection()
    {
    }

    void handle_qued_callback()
    {
    }

    bool release_protocol()
    {
      return true;
    }

    bool handle_recv(const void* /*data*/, size_t /*size*/)
    {
      return false;
    }
  };

  typedef epee::net_utils::boosted_tcp_server<test_protocol_handler> test_tcp_server;
}

TEST(boosted_tcp_server, worker_threads_are_exception_resistant)
{
  test_tcp_server srv(epee::net_utils::e_connection_type_RPC); // RPC disables network limit for unit tests
  ASSERT_TRUE(srv.init_server(test_server_port, test_server_host));

  boost::mutex mtx;
  boost::condition_variable cond;
  int counter = 0;

  auto counter_incrementer = [&counter, &cond, &mtx]()
  {
    boost::unique_lock<boost::mutex> lock(mtx);
    ++counter;
    if (4 <= counter)
    {
      cond.notify_one();
    }
  };

  // 2 theads, but 4 exceptions
  ASSERT_TRUE(srv.run_server(2, false));
  ASSERT_TRUE(srv.async_call([&counter_incrementer]() { counter_incrementer(); throw std::runtime_error("test 1"); }));
  ASSERT_TRUE(srv.async_call([&counter_incrementer]() { counter_incrementer(); throw std::string("test 2"); }));
  ASSERT_TRUE(srv.async_call([&counter_incrementer]() { counter_incrementer(); throw "test 3"; }));
  ASSERT_TRUE(srv.async_call([&counter_incrementer]() { counter_incrementer(); throw 4; }));

  {
    boost::unique_lock<boost::mutex> lock(mtx);
    ASSERT_NE(boost::cv_status::timeout, cond.wait_for(lock, boost::chrono::seconds(5)));
    ASSERT_EQ(4, counter);
  }

  // Check if threads are alive
  counter = 0;
  //auto counter_incrementer = [&counter]() { counter.fetch_add(1); epee::misc_utils::sleep_no_w(counter.load() * 10); };
  ASSERT_TRUE(srv.async_call(counter_incrementer));
  ASSERT_TRUE(srv.async_call(counter_incrementer));
  ASSERT_TRUE(srv.async_call(counter_incrementer));
  ASSERT_TRUE(srv.async_call(counter_incrementer));

  {
    boost::unique_lock<boost::mutex> lock(mtx);
    ASSERT_NE(boost::cv_status::timeout, cond.wait_for(lock, boost::chrono::seconds(5)));
    ASSERT_EQ(4, counter);
  }

  srv.send_stop_signal();
  ASSERT_TRUE(srv.timed_wait_server_stop(5 * 1000));
  ASSERT_TRUE(srv.deinit_server());
}
