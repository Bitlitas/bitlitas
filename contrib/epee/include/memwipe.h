// Copyright (c) 2018, Bitlitas
// All rights reserved.

#pragma once

#ifdef __cplusplus
#include <array>

extern "C" {
#endif

void *memwipe(void *src, size_t n);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace tools {

  /// Scrubs data in the contained type upon destruction.
  ///
  /// Primarily useful for making sure that private keys don't stick around in
  /// memory after the objects that held them have gone out of scope.
  template <class T>
  struct scrubbed : public T {
    using type = T;

    ~scrubbed() {
      scrub();
    }

    /// Destroy the contents of the contained type.
    void scrub() {
      static_assert(std::is_pod<T>::value,
                    "T cannot be auto-scrubbed. T must be POD.");
      static_assert(std::is_trivially_destructible<T>::value,
                    "T cannot be auto-scrubbed. T must be trivially destructable.");
      memwipe(this, sizeof(T));
    }
  };

  template <class T, size_t N>
  using scrubbed_arr = scrubbed<std::array<T, N>>;
} // namespace tools

// Partial specialization for std::is_pod<tools::scrubbed<T>> so that it can
// pretend to be the containted type in those contexts.
namespace std
{
  template<class t_scrubbee>
  struct is_pod<tools::scrubbed<t_scrubbee>> {
    static const bool value = is_pod<t_scrubbee>::value;
  };
}

#endif // __cplusplus
