// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <string>
#include <stdio.h>
#include <memory>
#include "misc_log_ex.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "perf"

namespace tools
{

class PerformanceTimer;

extern el::Level performance_timer_log_level;

class PerformanceTimer
{
public:
  PerformanceTimer(const std::string &s, uint64_t unit, el::Level l = el::Level::Debug);
  ~PerformanceTimer();
  void pause();
  void resume();

private:
  std::string name;
  uint64_t unit;
  el::Level level;
  uint64_t ticks;
  bool started;
  bool paused;
};

void set_performance_timer_log_level(el::Level level);

#define PERF_TIMER_UNIT(name, unit) tools::PerformanceTimer pt_##name(#name, unit, tools::performance_timer_log_level)
#define PERF_TIMER_UNIT_L(name, unit, l) tools::PerformanceTimer pt_##name(#name, unit, l)
#define PERF_TIMER(name) PERF_TIMER_UNIT(name, 1000)
#define PERF_TIMER_L(name, l) PERF_TIMER_UNIT_L(name, 1000, l)
#define PERF_TIMER_START_UNIT(name, unit) std::unique_ptr<tools::PerformanceTimer> pt_##name(new tools::PerformanceTimer(#name, unit, el::Level::Info))
#define PERF_TIMER_START(name) PERF_TIMER_START_UNIT(name, 1000)
#define PERF_TIMER_STOP(name) do { pt_##name.reset(NULL); } while(0)
#define PERF_TIMER_PAUSE(name) pt_##name->pause()
#define PERF_TIMER_RESUME(name) pt_##name->resume()

}
