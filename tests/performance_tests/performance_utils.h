// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <iostream>

#include <boost/config.hpp>

#ifdef BOOST_WINDOWS
#include <windows.h>
#endif

void set_process_affinity(int core)
{
#if defined (__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__sun)
    return;
#elif defined(BOOST_WINDOWS)
  DWORD_PTR mask = 1;
  for (int i = 0; i < core; ++i)
  {
    mask <<= 1;
  }
  ::SetProcessAffinityMask(::GetCurrentProcess(), core);
#elif defined(BOOST_HAS_PTHREADS)
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(core, &cpuset);
  if (0 != ::pthread_setaffinity_np(::pthread_self(), sizeof(cpuset), &cpuset))
  {
    std::cout << "pthread_setaffinity_np - ERROR" << std::endl;
  }
#endif
}

void set_thread_high_priority()
{
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__sun)
    return;
#elif defined(BOOST_WINDOWS)
  ::SetPriorityClass(::GetCurrentProcess(), HIGH_PRIORITY_CLASS);
#elif defined(BOOST_HAS_PTHREADS)
  pthread_attr_t attr;
  int policy = 0;
  int max_prio_for_policy = 0;

  ::pthread_attr_init(&attr);
  ::pthread_attr_getschedpolicy(&attr, &policy);
  max_prio_for_policy = ::sched_get_priority_max(policy);

  if (0 != ::pthread_setschedprio(::pthread_self(), max_prio_for_policy))
  {
    std::cout << "pthread_setschedprio - ERROR" << std::endl;
  }

  ::pthread_attr_destroy(&attr);
#endif
}
