// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"
#include "common/command_line.h"

TEST(CommandLine, IsYes)
{
  EXPECT_TRUE(command_line::is_yes("Y"));
  EXPECT_TRUE(command_line::is_yes("y"));
  EXPECT_TRUE(command_line::is_yes("YES"));
  EXPECT_TRUE(command_line::is_yes("YEs"));
  EXPECT_TRUE(command_line::is_yes("YeS"));
  EXPECT_TRUE(command_line::is_yes("yES"));
  EXPECT_TRUE(command_line::is_yes("Yes"));
  EXPECT_TRUE(command_line::is_yes("yeS"));
  EXPECT_TRUE(command_line::is_yes("yEs"));
  EXPECT_TRUE(command_line::is_yes("yes"));

  EXPECT_FALSE(command_line::is_yes(""));
  EXPECT_FALSE(command_line::is_yes("yes-"));
  EXPECT_FALSE(command_line::is_yes("NO"));
  EXPECT_FALSE(command_line::is_yes("No"));
  EXPECT_FALSE(command_line::is_yes("nO"));
  EXPECT_FALSE(command_line::is_yes("no"));
}
