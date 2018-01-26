// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include <string>
#include <ctime>

namespace Bitlitas {

class TransactionHistoryImpl;

class TransactionInfoImpl : public TransactionInfo
{
public:
    TransactionInfoImpl();
    ~TransactionInfoImpl();
    //! in/out
    virtual int direction() const;
    //! true if hold
    virtual bool isPending() const;
    virtual bool isFailed() const;
    virtual uint64_t amount() const;
    //! always 0 for incoming txes
    virtual uint64_t fee() const;
    virtual uint64_t blockHeight() const;
    virtual std::set<uint32_t> subaddrIndex() const;
    virtual uint32_t subaddrAccount() const;
    virtual std::string label() const;

    virtual std::string hash() const;
    virtual std::time_t timestamp() const;
    virtual std::string paymentId() const;
    virtual const std::vector<Transfer> &transfers() const;
    virtual uint64_t confirmations() const;
    virtual uint64_t unlockTime() const;

private:
    int         m_direction;
    bool        m_pending;
    bool        m_failed;
    uint64_t    m_amount;
    uint64_t    m_fee;
    uint64_t    m_blockheight;
    std::set<uint32_t> m_subaddrIndex;        // always unique index for incoming transfers; can be multiple indices for outgoing transfers
    uint32_t m_subaddrAccount;
    std::string m_label;
    std::string m_hash;
    std::time_t m_timestamp;
    std::string m_paymentid;
    std::vector<Transfer> m_transfers;
    uint64_t    m_confirmations;
    uint64_t    m_unlock_time;

    friend class TransactionHistoryImpl;

};

} // namespace

namespace Bitbitlitas = Bitlitas;
