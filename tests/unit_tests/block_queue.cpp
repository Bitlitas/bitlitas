// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero. 

#include <boost/uuid/uuid.hpp>
#include "gtest/gtest.h"
#include "crypto/crypto.h"
#include "cryptonote_protocol/cryptonote_protocol_defs.h"
#include "cryptonote_protocol/block_queue.h"

static const boost::uuids::uuid &uuid1()
{
  static const boost::uuids::uuid uuid = crypto::rand<boost::uuids::uuid>();
  return uuid;
}

static const boost::uuids::uuid &uuid2()
{
  static const boost::uuids::uuid uuid = crypto::rand<boost::uuids::uuid>();
  return uuid;
}

TEST(block_queue, empty)
{
  cryptonote::block_queue bq;
  ASSERT_EQ(bq.get_max_block_height(), 0);
}

TEST(block_queue, add_stepwise)
{
  cryptonote::block_queue bq;
  bq.add_blocks(0, 200, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 199);
  bq.add_blocks(200, 200, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 399);
  bq.add_blocks(401, 200, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 600);
  bq.add_blocks(400, 10, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 600);
}

TEST(block_queue, flush_uuid)
{
  cryptonote::block_queue bq;

  bq.add_blocks(0, 200, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 199);
  bq.add_blocks(200, 200, uuid2());
  ASSERT_EQ(bq.get_max_block_height(), 399);
  bq.flush_spans(uuid2());
  ASSERT_EQ(bq.get_max_block_height(), 199);
  bq.flush_spans(uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 0);

  bq.add_blocks(0, 200, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 199);
  bq.add_blocks(200, 200, uuid2());
  ASSERT_EQ(bq.get_max_block_height(), 399);
  bq.flush_spans(uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 399);
  bq.add_blocks(0, 200, uuid1());
  ASSERT_EQ(bq.get_max_block_height(), 399);
}
