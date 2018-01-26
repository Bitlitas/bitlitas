// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include "wallet/wallet2.h"

namespace Bitlitas {

class WalletImpl;

class SubaddressAccountImpl : public SubaddressAccount
{
public:
    SubaddressAccountImpl(WalletImpl * wallet);
    ~SubaddressAccountImpl();
    
    // Fetches addresses from Wallet2
    void refresh();
    std::vector<SubaddressAccountRow*> getAll() const;
    void addRow(const std::string &label);
    void setLabel(uint32_t accountIndex, const std::string &label);

private:
    void clearRows();
    
private:
    WalletImpl *m_wallet;
    std::vector<SubaddressAccountRow*> m_rows;
};

}
