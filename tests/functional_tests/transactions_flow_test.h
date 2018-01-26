// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

bool transactions_flow_test(std::string& working_folder, 
                            std::string path_source_wallet, 
                            std::string path_target_wallet, 
                            std::string& daemon_addr_a, 
                            std::string& daemon_addr_b, 
                            uint64_t amount_to_transfer, size_t mix_in_factor, size_t transactions_count, size_t transactions_per_second);
