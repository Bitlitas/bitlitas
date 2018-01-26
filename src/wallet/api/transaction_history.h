// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include <boost/thread/shared_mutex.hpp>

namespace Bitlitas {

class WalletImpl;

class TransactionHistoryImpl : public TransactionHistory
{
public:
    TransactionHistoryImpl(WalletImpl * wallet);
    ~TransactionHistoryImpl();
    virtual int count() const;
    virtual TransactionInfo * transaction(int index)  const;
    virtual TransactionInfo * transaction(const std::string &id) const;
    virtual std::vector<TransactionInfo*> getAll() const;
    virtual void refresh();

private:

    // TransactionHistory is responsible of memory management
    std::vector<TransactionInfo*> m_history;
    WalletImpl *m_wallet;
    mutable boost::shared_mutex   m_historyMutex;
};

}

namespace Bitbitlitas = Bitlitas;

