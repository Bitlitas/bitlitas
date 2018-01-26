// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "p2p/net_node_common.h"
#include "cryptonote_protocol/cryptonote_protocol_defs.h"
#include "cryptonote_basic/connection_context.h"
namespace cryptonote
{
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct i_cryptonote_protocol
  {
    virtual bool relay_block(NOTIFY_NEW_BLOCK::request& arg, cryptonote_connection_context& exclude_context)=0;
    virtual bool relay_transactions(NOTIFY_NEW_TRANSACTIONS::request& arg, cryptonote_connection_context& exclude_context)=0;
    //virtual bool request_objects(NOTIFY_REQUEST_GET_OBJECTS::request& arg, cryptonote_connection_context& context)=0;
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct cryptonote_protocol_stub: public i_cryptonote_protocol
  {
    virtual bool relay_block(NOTIFY_NEW_BLOCK::request& arg, cryptonote_connection_context& exclude_context)
    {
      return false;
    }
    virtual bool relay_transactions(NOTIFY_NEW_TRANSACTIONS::request& arg, cryptonote_connection_context& exclude_context)
    {
      return false;
    }

  };
}
