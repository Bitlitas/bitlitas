// Copyright (c) 2018, Bitlitas
// All rights reserved.

#pragma once

#include <stddef.h>
#include <vector>
#include <string>

namespace epee
{
  class wipeable_string
  {
  public:
    wipeable_string() {}
    wipeable_string(const wipeable_string &other);
    wipeable_string(wipeable_string &&other);
    wipeable_string(const std::string &other);
    wipeable_string(std::string &&other);
    wipeable_string(const char *s);
    ~wipeable_string();
    void wipe();
    void push_back(char c);
    void pop_back();
    const char *data() const noexcept { return buffer.data(); }
    size_t size() const noexcept { return buffer.size(); }
    bool empty() const noexcept { return buffer.empty(); }
    void resize(size_t sz);
    void reserve(size_t sz);
    void clear();
    bool operator==(const wipeable_string &other) const noexcept { return buffer == other.buffer; }
    bool operator!=(const wipeable_string &other) const noexcept { return buffer != other.buffer; }
    wipeable_string &operator=(wipeable_string &&other);
    wipeable_string &operator=(const wipeable_string &other);

    static void set_wipe(void *(*f)(void*, size_t)) { wipefunc = f; }

  private:
    void grow(size_t sz, size_t reserved = 0);

  private:
    std::vector<char> buffer;
    static void *(*wipefunc)(void*, size_t);
  };
}
