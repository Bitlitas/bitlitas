// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"

#include "common/util.h"

TEST(vercmp, empty) { ASSERT_TRUE(tools::vercmp("", "") == 0); }
TEST(vercmp, empty0) { ASSERT_TRUE(tools::vercmp("", "0") == 0); }
TEST(vercmp, empty1) { ASSERT_TRUE(tools::vercmp("0", "") == 0); }
TEST(vercmp, zero_zero) { ASSERT_TRUE(tools::vercmp("0", "0") == 0); }
TEST(vercmp, one_one) { ASSERT_TRUE(tools::vercmp("1", "1") == 0); }
TEST(vercmp, one_two) { ASSERT_TRUE(tools::vercmp("1", "2") < 0); }
TEST(vercmp, two_one) { ASSERT_TRUE(tools::vercmp("2", "1") > 0); }
TEST(vercmp, ten_nine) { ASSERT_TRUE(tools::vercmp("10", "9") > 0); }
TEST(vercmp, one_dot_ten_one_dot_nine) { ASSERT_TRUE(tools::vercmp("1.10", "1.9") > 0); }
TEST(vercmp, one_one_dot_nine) { ASSERT_TRUE(tools::vercmp("1", "1.9") < 0); }
TEST(vercmp, to_master) { ASSERT_TRUE(tools::vercmp("1.0", "1.0-master") < 0); }
TEST(vercmp, from_master) { ASSERT_TRUE(tools::vercmp("1.0-master", "1.1") < 0); }

