// Copyright (c) 2018, Bitlitas
// All rights reserved.

#include <string.h>
#include "misc_log_ex.h"
#include "wipeable_string.h"

namespace epee
{

void *(*wipeable_string::wipefunc)(void*, size_t) = NULL;

wipeable_string::wipeable_string(const wipeable_string &other):
  buffer(other.buffer)
{
}

wipeable_string::wipeable_string(wipeable_string &&other)
{
  if (&other == this)
    return;
  buffer = std::move(other.buffer);
}

wipeable_string::wipeable_string(const std::string &other)
{
  grow(other.size());
  memcpy(buffer.data(), other.c_str(), size());
}

wipeable_string::wipeable_string(std::string &&other)
{
  CHECK_AND_ASSERT_THROW_MES(wipefunc, "wipefunc is not set");
  grow(other.size());
  memcpy(buffer.data(), other.c_str(), size());
  if (!other.empty())
  {
    wipefunc(&other[0], other.size()); // we're kinda left with this again aren't we
    other = std::string();
  }
}

wipeable_string::wipeable_string(const char *s)
{
  grow(strlen(s));
  memcpy(buffer.data(), s, size());
}

wipeable_string::~wipeable_string()
{
  wipe();
}

void wipeable_string::wipe()
{
  CHECK_AND_ASSERT_THROW_MES(wipefunc, "wipefunc is not set");
  wipefunc(buffer.data(), buffer.size() * sizeof(char));
}

void wipeable_string::grow(size_t sz, size_t reserved)
{
  CHECK_AND_ASSERT_THROW_MES(wipefunc, "wipefunc is not set");
  if (reserved < sz)
    reserved = sz;
  if (reserved <= buffer.capacity())
  {
    if (sz < buffer.size())
      wipefunc(buffer.data() + sz, buffer.size() - sz);
    buffer.resize(sz);
    return;
  }
  size_t old_sz = buffer.size();
  std::unique_ptr<char[]> tmp{new char[old_sz]};
  memcpy(tmp.get(), buffer.data(), old_sz * sizeof(char));
  wipefunc(buffer.data(), old_sz * sizeof(char));
  buffer.reserve(reserved);
  buffer.resize(sz);
  memcpy(buffer.data(), tmp.get(), old_sz * sizeof(char));
  wipefunc(tmp.get(), old_sz * sizeof(char));
}

void wipeable_string::push_back(char c)
{
  grow(size() + 1);
  buffer.back() = c;
}

void wipeable_string::pop_back()
{
  resize(size() - 1);
}

void wipeable_string::resize(size_t sz)
{
  grow(sz);
}

void wipeable_string::reserve(size_t sz)
{
  grow(size(), sz);
}

void wipeable_string::clear()
{
  resize(0);
}

wipeable_string &wipeable_string::operator=(wipeable_string &&other)
{
  if (&other != this)
    buffer = std::move(other.buffer);
  return *this;
}

wipeable_string &wipeable_string::operator=(const wipeable_string &other)
{
  if (&other != this)
    buffer = other.buffer;
  return *this;
}

}
