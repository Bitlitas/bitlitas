// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <vector>
#include "misc_os_dependent.h"
#include "perf_timer.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "perf"

namespace tools
{

el::Level performance_timer_log_level = el::Level::Debug;

static __thread std::vector<PerformanceTimer*> *performance_timers = NULL;

void set_performance_timer_log_level(el::Level level)
{
  if (level != el::Level::Debug && level != el::Level::Trace && level != el::Level::Info
   && level != el::Level::Warning && level != el::Level::Error && level != el::Level::Fatal)
  {
    MERROR("Wrong log level: " << el::LevelHelper::convertToString(level) << ", using Debug");
    level = el::Level::Debug;
  }
  performance_timer_log_level = level;
}

PerformanceTimer::PerformanceTimer(const std::string &s, uint64_t unit, el::Level l): name(s), unit(unit), level(l), started(false)
{
  ticks = epee::misc_utils::get_ns_count();
  if (!performance_timers)
  {
    MLOG(level, "PERF             ----------");
    performance_timers = new std::vector<PerformanceTimer*>();
  }
  else
  {
    PerformanceTimer *pt = performance_timers->back();
    if (!pt->started)
    {
      MLOG(pt->level, "PERF           " << std::string((performance_timers->size()-1) * 2, ' ') << "  " << pt->name);
      pt->started = true;
    }
  }
  performance_timers->push_back(this);
}

PerformanceTimer::~PerformanceTimer()
{
  performance_timers->pop_back();
  ticks = epee::misc_utils::get_ns_count() - ticks;
  char s[12];
  snprintf(s, sizeof(s), "%8llu  ", (unsigned long long)ticks / (1000000000 / unit));
  MLOG(level, "PERF " << s << std::string(performance_timers->size() * 2, ' ') << "  " << name);
  if (performance_timers->empty())
  {
    delete performance_timers;
    performance_timers = NULL;
  }
}

}
