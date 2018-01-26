// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <cstdint>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <string>

#include "cryptonote_basic/cryptonote_basic_impl.h"

namespace
{
  static constexpr const std::uint8_t source[] = {
    0x8b, 0x65, 0x59, 0x70, 0x15, 0x37, 0x99, 0xaf, 0x2a, 0xea, 0xdc, 0x9f, 0xf1, 0xad, 0xd0, 0xea,
    0x6c, 0x72, 0x51, 0xd5, 0x41, 0x54, 0xcf, 0xa9, 0x2c, 0x17, 0x3a, 0x0d, 0xd3, 0x9c, 0x1f, 0x94,
    0x6c, 0x72, 0x51, 0xd5, 0x41, 0x54, 0xcf, 0xa9, 0x2c, 0x17, 0x3a, 0x0d, 0xd3, 0x9c, 0x1f, 0x94,
    0x8b, 0x65, 0x59, 0x70, 0x15, 0x37, 0x99, 0xaf, 0x2a, 0xea, 0xdc, 0x9f, 0xf1, 0xad, 0xd0, 0xea
  };

  static constexpr const char expected[] =
    "8b655970153799af2aeadc9ff1add0ea6c7251d54154cfa92c173a0dd39c1f94"
    "6c7251d54154cfa92c173a0dd39c1f948b655970153799af2aeadc9ff1add0ea";

  template<typename T>
  bool is_formatted()
  {
    T value{};

    static_assert(alignof(T) == 1, "T must have 1 byte alignment");
    static_assert(sizeof(T) <= sizeof(source), "T is too large for source");
    static_assert(sizeof(T) * 2 <= sizeof(expected), "T is too large for destination");
    std::memcpy(std::addressof(value), source, sizeof(T));

    std::stringstream out;
    out << "BEGIN" << value << "END";  
    return out.str() == "BEGIN<" + std::string{expected, sizeof(T) * 2} + ">END";
  }
}

TEST(Crypto, Ostream)
{
  EXPECT_TRUE(is_formatted<crypto::hash8>());
  EXPECT_TRUE(is_formatted<crypto::hash>());
  EXPECT_TRUE(is_formatted<crypto::public_key>());
  EXPECT_TRUE(is_formatted<crypto::secret_key>());
  EXPECT_TRUE(is_formatted<crypto::signature>());
  EXPECT_TRUE(is_formatted<crypto::key_derivation>());
  EXPECT_TRUE(is_formatted<crypto::key_image>());
}
