// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "transaction_info.h"

using namespace std;

namespace Bitlitas {

TransactionInfo::~TransactionInfo() {}

TransactionInfo::Transfer::Transfer(uint64_t _amount, const string &_address)
    : amount(_amount), address(_address) {}


TransactionInfoImpl::TransactionInfoImpl()
    : m_direction(Direction_Out)
      , m_pending(false)
      , m_failed(false)
      , m_amount(0)
      , m_fee(0)
      , m_blockheight(0)
      , m_subaddrAccount(0)
      , m_timestamp(0)
      , m_confirmations(0)
      , m_unlock_time(0)
{

}

TransactionInfoImpl::~TransactionInfoImpl()
{

}

int TransactionInfoImpl::direction() const
{
    return m_direction;
}


bool TransactionInfoImpl::isPending() const
{
    return m_pending;
}

bool TransactionInfoImpl::isFailed() const
{
    return m_failed;
}

uint64_t TransactionInfoImpl::amount() const
{
    return m_amount;
}

uint64_t TransactionInfoImpl::fee() const
{
    return m_fee;
}

uint64_t TransactionInfoImpl::blockHeight() const
{
    return m_blockheight;
}

std::set<uint32_t> TransactionInfoImpl::subaddrIndex() const
{
    return m_subaddrIndex;
}

uint32_t TransactionInfoImpl::subaddrAccount() const
{
    return m_subaddrAccount;
}

string TransactionInfoImpl::label() const
{
    return m_label;
}


string TransactionInfoImpl::hash() const
{
    return m_hash;
}

std::time_t TransactionInfoImpl::timestamp() const
{
    return m_timestamp;
}

string TransactionInfoImpl::paymentId() const
{
    return m_paymentid;
}

const std::vector<TransactionInfo::Transfer> &TransactionInfoImpl::transfers() const
{
    return m_transfers;
}

uint64_t TransactionInfoImpl::confirmations() const
{
    return m_confirmations;
}

uint64_t TransactionInfoImpl::unlockTime() const
{
    return m_unlock_time;
}

} // namespace

namespace Bitbitlitas = Bitlitas;
