// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace tools
{
//! A global thread pool
class threadpool
{
public:
  static threadpool& getInstance() {
    static threadpool instance;
    return instance;
  }

  // The waiter lets the caller know when all of its
  // tasks are completed.
  class waiter {
    boost::mutex mt;
    boost::condition_variable cv;
    int num;
    public:
    void inc();
    void dec();
    void wait();  //! Wait for a set of tasks to finish.
    waiter() : num(0){}
    ~waiter() { wait(); }
  };

  // Submit a task to the pool. The waiter pointer may be
  // NULL if the caller doesn't care to wait for the
  // task to finish.
  void submit(waiter *waiter, std::function<void()> f);

  int get_max_concurrency();

  private:
    threadpool();
    ~threadpool();
    typedef struct entry {
      waiter *wo;
      std::function<void()> f;
    } entry;
    std::deque<entry> queue;
    boost::condition_variable has_work;
    boost::mutex mutex;
    std::vector<boost::thread> threads;
    int active;
    int max;
    bool running;
    void run();
};

}
