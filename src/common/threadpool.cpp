// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "common/threadpool.h"

#include <cassert>
#include <limits>
#include <stdexcept>

#include "cryptonote_config.h"
#include "common/util.h"

static __thread int depth = 0;

namespace tools
{
threadpool::threadpool() : running(true), active(0) {
  boost::thread::attributes attrs;
  attrs.set_stack_size(THREAD_STACK_SIZE);
  max = tools::get_max_concurrency();
  size_t i = max;
  while(i--) {
    threads.push_back(boost::thread(attrs, boost::bind(&threadpool::run, this)));
  }
}

threadpool::~threadpool() {
  {
    const boost::unique_lock<boost::mutex> lock(mutex);
    running = false;
    has_work.notify_all();
  }
  for (size_t i = 0; i<threads.size(); i++) {
    threads[i].join();
  }
}

void threadpool::submit(waiter *obj, std::function<void()> f) {
  entry e = {obj, f};
  boost::unique_lock<boost::mutex> lock(mutex);
  if ((active == max && !queue.empty()) || depth > 0) {
    // if all available threads are already running
    // and there's work waiting, just run in current thread
    lock.unlock();
    ++depth;
    f();
    --depth;
  } else {
    if (obj)
      obj->inc();
    queue.push_back(e);
    has_work.notify_one();
  }
}

int threadpool::get_max_concurrency() {
  return max;
}

void threadpool::waiter::wait() {
  boost::unique_lock<boost::mutex> lock(mt);
  while(num) cv.wait(lock);
}

void threadpool::waiter::inc() {
  const boost::unique_lock<boost::mutex> lock(mt);
  num++;
}

void threadpool::waiter::dec() {
  const boost::unique_lock<boost::mutex> lock(mt);
  num--;
  if (!num)
    cv.notify_one();
}

void threadpool::run() {
  boost::unique_lock<boost::mutex> lock(mutex);
  while (running) {
    entry e;
    while(queue.empty() && running)
      has_work.wait(lock);
    if (!running) break;

    active++;
    e = queue.front();
    queue.pop_front();
    lock.unlock();
    ++depth;
    e.f();
    --depth;

    if (e.wo)
      e.wo->dec();
    lock.lock();
    active--;
  }
}
}
