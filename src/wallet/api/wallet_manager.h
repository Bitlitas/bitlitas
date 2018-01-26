// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "wallet/api/wallet2_api.h"
#include <string>

namespace Bitlitas {

class WalletManagerImpl : public WalletManager
{
public:
    Wallet * createWallet(const std::string &path, const std::string &password,
                          const std::string &language, bool testnet);
    Wallet * openWallet(const std::string &path, const std::string &password, bool testnet);
    virtual Wallet * recoveryWallet(const std::string &path, const std::string &memo, bool testnet, uint64_t restoreHeight);
    virtual Wallet * createWalletFromKeys(const std::string &path, 
                                                    const std::string &language,
                                                    bool testnet, 
                                                    uint64_t restoreHeight,
                                                    const std::string &addressString,
                                                    const std::string &viewKeyString,
                                                    const std::string &spendKeyString = "");
    virtual bool closeWallet(Wallet *wallet, bool store = true);
    bool walletExists(const std::string &path);
    bool verifyWalletPassword(const std::string &keys_file_name, const std::string &password, bool no_spend_key) const;
    std::vector<std::string> findWallets(const std::string &path);
    std::string errorString() const;
    void setDaemonAddress(const std::string &address);
    bool connected(uint32_t *version = NULL) const;
    uint64_t blockchainHeight() const;
    uint64_t blockchainTargetHeight() const;
    uint64_t networkDifficulty() const;
    double miningHashRate() const;
    uint64_t blockTarget() const;
    bool isMining() const;
    bool startMining(const std::string &address, uint32_t threads = 1, bool background_mining = false, bool ignore_battery = true);
    bool stopMining();
    std::string resolveOpenAlias(const std::string &address, bool &dnssec_valid) const;

private:
    WalletManagerImpl() {}
    friend struct WalletManagerFactory;
    std::string m_daemonAddress;
    std::string m_errorString;
};

} // namespace

namespace Bitbitlitas = Bitlitas;
