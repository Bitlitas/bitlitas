// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_boost_serialization.h"
#include "cryptonote_core/blockchain.h"
#include "blockchain_db/blockchain_db.h"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <boost/iostreams/copy.hpp>
#include <atomic>

#include "common/command_line.h"
#include "version.h"

#include "blockchain_utilities.h"


using namespace cryptonote;


class BlocksdatFile
{
public:

  bool store_blockchain_raw(cryptonote::Blockchain* cs, cryptonote::tx_memory_pool* txp,
      boost::filesystem::path& output_file, uint64_t use_block_height=0);

protected:

  Blockchain* m_blockchain_storage;

  std::ofstream * m_raw_data_file;

  // open export file for write
  bool open_writer(const boost::filesystem::path& file_path, uint64_t block_stop);
  bool initialize_file(uint64_t block_stop);
  bool close();
  void write_block(const crypto::hash &block_hash);

private:

  uint64_t m_cur_height; // tracks current height during export
  std::vector<crypto::hash> m_hashes;
};
