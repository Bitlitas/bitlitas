// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <sstream>
#include "binary_archive.h"

namespace serialization {
  /*! creates a new archive with the passed blob and serializes it into v
   */
  template <class T>
    bool parse_binary(const std::string &blob, T &v)
    {
      std::istringstream istr(blob);
      binary_archive<false> iar(istr);
      return ::serialization::serialize(iar, v);
    }

  /*! dumps the data in v into the blob string
   */
  template<class T>
    bool dump_binary(T& v, std::string& blob)
    {
      std::stringstream ostr;
      binary_archive<true> oar(ostr);
      bool success = ::serialization::serialize(oar, v);
      blob = ostr.str();
      return success && ostr.good();
    };

}
