// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include "wallet/wallet2.h"

namespace Bitlitas {

class WalletImpl;

class SubaddressImpl : public Subaddress
{
public:
    SubaddressImpl(WalletImpl * wallet);
    ~SubaddressImpl();
    
    // Fetches addresses from Wallet2
    void refresh(uint32_t accountIndex);
    std::vector<SubaddressRow*> getAll() const;
    void addRow(uint32_t accountIndex, const std::string &label);
    void setLabel(uint32_t accountIndex, uint32_t addressIndex, const std::string &label);

private:
    void clearRows();
    
private:
    WalletImpl *m_wallet;
    std::vector<SubaddressRow*> m_rows;
};

}
