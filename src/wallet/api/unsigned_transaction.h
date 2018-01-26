// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include "wallet/wallet2.h"

#include <string>
#include <vector>


namespace Bitlitas {

class WalletImpl;
class UnsignedTransactionImpl : public UnsignedTransaction
{
public:
    UnsignedTransactionImpl(WalletImpl &wallet);
    ~UnsignedTransactionImpl();
    int status() const;
    std::string errorString() const;
    std::vector<uint64_t> amount() const;
    std::vector<uint64_t> dust() const;
    std::vector<uint64_t> fee() const;
    std::vector<uint64_t> mixin() const;
    std::vector<std::string> paymentId() const;
    std::vector<std::string> recipientAddress() const;
    uint64_t txCount() const;
    // sign txs and save to file
    bool sign(const std::string &signedFileName);
    std::string confirmationMessage() const {return m_confirmationMessage;}
    uint64_t minMixinCount() const;

private:
    // Callback function to check all loaded tx's and generate confirmationMessage
    bool checkLoadedTx(const std::function<size_t()> get_num_txes, const std::function<const tools::wallet2::tx_construction_data&(size_t)> &get_tx, const std::string &extra_message);
    
    friend class WalletImpl;
    WalletImpl &m_wallet;

    int  m_status;
    std::string m_errorString;
    tools::wallet2::unsigned_tx_set m_unsigned_tx_set;
    std::string m_confirmationMessage;
};


}

namespace Bitbitlitas = Bitlitas;
