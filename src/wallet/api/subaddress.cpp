// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "subaddress.h"
#include "wallet.h"
#include "crypto/hash.h"
#include "wallet/wallet2.h"
#include "common_defines.h"

#include <vector>

namespace Bitlitas {
  
Subaddress::~Subaddress() {}
  
SubaddressImpl::SubaddressImpl(WalletImpl *wallet)
    : m_wallet(wallet) {}

void SubaddressImpl::addRow(uint32_t accountIndex, const std::string &label)
{
  m_wallet->m_wallet->add_subaddress(accountIndex, label);
  refresh(accountIndex);
}

void SubaddressImpl::setLabel(uint32_t accountIndex, uint32_t addressIndex, const std::string &label)
{
  try
  {
    m_wallet->m_wallet->set_subaddress_label({accountIndex, addressIndex}, label);
    refresh(accountIndex);
  }
  catch (const std::exception& e)
  {
    LOG_ERROR("setLabel: " << e.what());
  }
}

void SubaddressImpl::refresh(uint32_t accountIndex) 
{
  LOG_PRINT_L2("Refreshing subaddress");
  
  clearRows();
  for (size_t i = 0; i < m_wallet->m_wallet->get_num_subaddresses(accountIndex); ++i)
  {
    m_rows.push_back(new SubaddressRow(i, m_wallet->m_wallet->get_subaddress_as_str({accountIndex, (uint32_t)i}), m_wallet->m_wallet->get_subaddress_label({accountIndex, (uint32_t)i})));
  }
}

void SubaddressImpl::clearRows() {
   for (auto r : m_rows) {
     delete r;
   }
   m_rows.clear();
}

std::vector<SubaddressRow*> SubaddressImpl::getAll() const
{
  return m_rows;
}

SubaddressImpl::~SubaddressImpl()
{
  clearRows();
}

} // namespace
