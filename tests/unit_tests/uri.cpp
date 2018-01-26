// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "gtest/gtest.h"
#include "wallet/wallet2.h"

#define TEST_ADDRESS "9tTLtauaEKSj7xoVXytVH32R1pLZBk4VV4mZFGEh4wkXhDWqw1soPyf3fGixf1kni31VznEZkWNEza9d5TvjWwq5PaohYHC"
#define TEST_INTEGRATED_ADDRESS "A4A1uPj4qaxj7xoVXytVH32R1pLZBk4VV4mZFGEh4wkXhDWqw1soPyf3fGixf1kni31VznEZkWNEza9d5TvjWwq5acaPMJfMbn3ReTsBpp"
// included payment id: <f612cac0b6cb1cda>

#define PARSE_URI(uri, expected) \
  std::string address, payment_id, recipient_name, description, error; \
  uint64_t amount; \
  std::vector<std::string> unknown_parameters; \
  tools::wallet2 w(true); \
  bool ret = w.parse_uri(uri, address, payment_id, amount, description, recipient_name, unknown_parameters, error); \
  ASSERT_EQ(ret, expected);

TEST(uri, empty_string)
{
  PARSE_URI("", false);
}

TEST(uri, no_scheme)
{
  PARSE_URI("bitlitas", false);
}

TEST(uri, bad_scheme)
{
  PARSE_URI("http://foo", false);
}

TEST(uri, scheme_not_first)
{
  PARSE_URI(" bitlitas:", false);
}

TEST(uri, no_body)
{
  PARSE_URI("bitlitas:", false);
}

TEST(uri, no_address)
{
  PARSE_URI("bitlitas:?", false);
}

TEST(uri, bad_address)
{
  PARSE_URI("bitlitas:44444", false);
}

TEST(uri, good_address)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS, true);
  ASSERT_EQ(address, TEST_ADDRESS);
}

TEST(uri, good_integrated_address)
{
  PARSE_URI("bitlitas:" TEST_INTEGRATED_ADDRESS, true);
}

TEST(uri, parameter_without_inter)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"&amount=1", false);
}

TEST(uri, parameter_without_equals)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?amount", false);
}

TEST(uri, parameter_without_value)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_amount=", false);
}

TEST(uri, negative_amount)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_amount=-1", false);
}

TEST(uri, bad_amount)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_amount=alphanumeric", false);
}

TEST(uri, duplicate_parameter)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_amount=1&tx_amount=1", false);
}

TEST(uri, unknown_parameter)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?unknown=1", true);
  ASSERT_EQ(unknown_parameters.size(), 1);
  ASSERT_EQ(unknown_parameters[0], "unknown=1");
}

TEST(uri, unknown_parameters)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_amount=1&unknown=1&tx_description=desc&foo=bar", true);
  ASSERT_EQ(unknown_parameters.size(), 2);
  ASSERT_EQ(unknown_parameters[0], "unknown=1");
  ASSERT_EQ(unknown_parameters[1], "foo=bar");
}

TEST(uri, empty_payment_id)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_payment_id=", false);
}

TEST(uri, bad_payment_id)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_payment_id=1234567890", false);
}

TEST(uri, short_payment_id)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_payment_id=1234567890123456", true);
  ASSERT_EQ(address, TEST_ADDRESS);
  ASSERT_EQ(payment_id, "1234567890123456");
}

TEST(uri, long_payment_id)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_payment_id=1234567890123456789012345678901234567890123456789012345678901234", true);
  ASSERT_EQ(address, TEST_ADDRESS);
  ASSERT_EQ(payment_id, "1234567890123456789012345678901234567890123456789012345678901234");
}

TEST(uri, payment_id_with_integrated_address)
{
  PARSE_URI("bitlitas:" TEST_INTEGRATED_ADDRESS"?tx_payment_id=1234567890123456", false);
}

TEST(uri, empty_description)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=", true);
  ASSERT_EQ(description, "");
}

TEST(uri, empty_recipient_name)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?recipient_name=", true);
  ASSERT_EQ(recipient_name, "");
}

TEST(uri, non_empty_description)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=foo", true);
  ASSERT_EQ(description, "foo");
}

TEST(uri, non_empty_recipient_name)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?recipient_name=foo", true);
  ASSERT_EQ(recipient_name, "foo");
}

TEST(uri, url_encoding)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=foo%20bar", true);
  ASSERT_EQ(description, "foo bar");
}

TEST(uri, non_alphanumeric_url_encoding)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=foo%2x", true);
  ASSERT_EQ(description, "foo%2x");
}

TEST(uri, truncated_url_encoding)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=foo%2", true);
  ASSERT_EQ(description, "foo%2");
}

TEST(uri, percent_without_url_encoding)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=foo%", true);
  ASSERT_EQ(description, "foo%");
}

TEST(uri, url_encoded_once)
{
  PARSE_URI("bitlitas:" TEST_ADDRESS"?tx_description=foo%2020", true);
  ASSERT_EQ(description, "foo 20");
}

