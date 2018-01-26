// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"                     // LOG_PRINT_x
#include "common/util.h"

using namespace std;

namespace Bitlitas {
namespace Utils {

bool isAddressLocal(const std::string &address)
{ 
    try {
        return tools::is_local_address(address);
    } catch (const std::exception &e) {
        MERROR("error: " << e.what());
        return false;
    }
}

void onStartup()
{
    tools::on_startup();
}

}


} // namespace

namespace Bitbitlitas = Bitlitas;
