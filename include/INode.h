// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <cstdint>
#include <system_error>

namespace CryptoNote {

class INodeObserver {
public:
  virtual void initCompleted(std::error_code result) {}

  virtual void peerCountUpdated(size_t count) {}
  virtual void lastLocalBlockHeightUpdated(uint64_t height) {}
  virtual void lastKnownBlockHeightUpdated(uint64_t height) {}

  virtual void blockchainReorganized(uint64_t height) {}
};

class INode {
public:
  virtual ~INode() = 0;
  virtual void addObserver(INodeObserver* observer) = 0;
  virtual void removeObserver(INodeObserver* observer) = 0;

  virtual void init() = 0;
  virtual void shutdown() = 0;

  virtual size_t getPeerCount() = 0;
  virtual uint64_t getLastLocalBlockHeight() = 0;
  virtual uint64_t getLastKnownBlockHeight() = 0;
};

}
