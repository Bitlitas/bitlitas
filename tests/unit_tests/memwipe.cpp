// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"

#include <stdint.h>
#include "misc_log_ex.h"
#include "memwipe.h"

// Probably won't catch the optimized out case, but at least we test
// it works in the normal case
static void test(bool wipe)
{
  char *foo = (char*)malloc(4);
  ASSERT_TRUE(foo != NULL);
  intptr_t foop = (intptr_t)foo;
  strcpy(foo, "bar");
  void *bar = wipe ? memwipe(foo, 3) : memset(foo, 0, 3);
  ASSERT_EQ(foo, bar);
  free(foo);
  char *quux = (char*)malloc(4); // same size, just after free, so we're likely to get the same, depending on the allocator
  if ((intptr_t)quux == foop)
  {
    MDEBUG(std::hex << std::setw(8) << std::setfill('0') << *(uint32_t*)quux);
    if (wipe) ASSERT_TRUE(memcmp(quux, "bar", 3));
  }
  else MWARNING("We did not get the same location, cannot check");
  free(quux);
}

TEST(memwipe, control)
{
  test(false);
}

TEST(memwipe, works)
{
  test(true);
}
