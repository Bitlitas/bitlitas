// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include "wallet/wallet2.h"

namespace Bitlitas {

class WalletImpl;

class AddressBookImpl : public AddressBook
{
public:
    AddressBookImpl(WalletImpl * wallet);
    ~AddressBookImpl();
    
    // Fetches addresses from Wallet2
    void refresh();
    std::vector<AddressBookRow*> getAll() const;
    bool addRow(const std::string &dst_addr , const std::string &payment_id, const std::string &description);
    bool deleteRow(std::size_t rowId);
     
    // Error codes. See AddressBook:ErrorCode enum in wallet2_api.h
    std::string errorString() const {return m_errorString;}
    int errorCode() const {return m_errorCode;}

    int lookupPaymentID(const std::string &payment_id) const;
    
private:
    void clearRows();
    void clearStatus();
    
private:
    WalletImpl *m_wallet;
    std::vector<AddressBookRow*> m_rows;
    std::string m_errorString;
    int m_errorCode;
};

}

namespace Bitbitlitas = Bitlitas;

