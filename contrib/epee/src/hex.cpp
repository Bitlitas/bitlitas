// Copyright (c) 2018, Bitlitas
// All rights reserved.

#include "hex.h"

#include <iterator>
#include <limits>
#include <ostream>
#include <stdexcept>

namespace epee
{
  namespace
  {
    template<typename T>
    void write_hex(T&& out, const span<const std::uint8_t> src)
    {
      static constexpr const char hex[] = u8"0123456789abcdef";
      static_assert(sizeof(hex) == 17, "bad string size");
      for (const std::uint8_t byte : src)
      {
        *out = hex[byte >> 4];
        ++out;
        *out = hex[byte & 0x0F];
        ++out;
      }
    }
  }

  std::string to_hex::string(const span<const std::uint8_t> src)
  {
    if (std::numeric_limits<std::size_t>::max() / 2 < src.size())
      throw std::range_error("hex_view::to_string exceeded maximum size");

    std::string out{};
    out.resize(src.size() * 2);
    buffer_unchecked(std::addressof(out[0]), src);
    return out;
  }

  void to_hex::buffer(std::ostream& out, const span<const std::uint8_t> src)
  {
    write_hex(std::ostreambuf_iterator<char>{out}, src);
  }

  void to_hex::formatted(std::ostream& out, const span<const std::uint8_t> src)
  {
    out.put('<');
    buffer(out, src);
    out.put('>');
  }

  void to_hex::buffer_unchecked(char* out, const span<const std::uint8_t> src) noexcept
  {
    return write_hex(out, src);
  }
}
