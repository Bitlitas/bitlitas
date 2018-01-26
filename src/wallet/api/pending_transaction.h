// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include "wallet/wallet2.h"

#include <string>
#include <vector>


namespace Bitlitas {

class WalletImpl;
class PendingTransactionImpl : public PendingTransaction
{
public:
    PendingTransactionImpl(WalletImpl &wallet);
    ~PendingTransactionImpl();
    int status() const;
    std::string errorString() const;
    bool commit(const std::string &filename = "", bool overwrite = false);
    uint64_t amount() const;
    uint64_t dust() const;
    uint64_t fee() const;
    std::vector<std::string> txid() const;
    uint64_t txCount() const;
    std::vector<uint32_t> subaddrAccount() const;
    std::vector<std::set<uint32_t>> subaddrIndices() const;
    // TODO: continue with interface;

private:
    friend class WalletImpl;
    WalletImpl &m_wallet;

    int  m_status;
    std::string m_errorString;
    std::vector<tools::wallet2::pending_tx> m_pending_tx;
};


}

namespace Bitbitlitas = Bitlitas;
