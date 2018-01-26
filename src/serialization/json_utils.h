// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <sstream>
#include "json_archive.h"

namespace serialization {

template<class T>
std::string dump_json(T &v)
{
  std::stringstream ostr;
  json_archive<true> oar(ostr);
  assert(serialization::serialize(oar, v));
  return ostr.str();
};

} // namespace serialization
