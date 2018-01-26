// Copyright (c) 2018, Bitlitas
// All rights reserved.

#pragma once

#include <array>
#include <cstdint>
#include <iosfwd>
#include <string>

#include "span.h"

namespace epee
{
  struct to_hex
  {
    //! \return A std::string containing hex of `src`.
    static std::string string(const span<const std::uint8_t> src);

    //! \return An array containing hex of `src`.
    template<std::size_t N>
    static std::array<char, N * 2> array(const std::array<std::uint8_t, N>& src) noexcept
    {
      std::array<char, N * 2> out{{}};
      static_assert(N <= 128, "keep the stack size down");
      buffer_unchecked(out.data(), {src.data(), src.size()});
      return out;
    }

    //! Append `src` as hex to `out`.
    static void buffer(std::ostream& out, const span<const std::uint8_t> src);

    //! Append `< + src + >` as hex to `out`.
    static void formatted(std::ostream& out, const span<const std::uint8_t> src);

  private:
    //! Write `src` bytes as hex to `out`. `out` must be twice the length
    static void buffer_unchecked(char* out, const span<const std::uint8_t> src) noexcept;
  };
}
