// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "ringct/rctSigs.h"
#include "cryptonote_basic/cryptonote_basic.h"

#include "single_tx_test_base.h"

template<size_t inputs, size_t ring_size, bool ver>
class test_ringct_mlsag : public single_tx_test_base
{
public:
  static const size_t cols = ring_size;
  static const size_t rows = inputs;
  static const size_t loop_count = 100;

  bool init()
  {
    if (!single_tx_test_base::init())
      return false;

    rct::keyV xtmp = rct::skvGen(rows);
    rct::keyM xm = rct::keyMInit(rows, cols);// = [[None]*N] #just used to generate test public keys
    sk = rct::skvGen(rows);
    P  = rct::keyMInit(rows, cols);// = keyM[[None]*N] #stores the public keys;
    ind = 2;
    for (size_t j = 0 ; j < rows ; j++)
    {
        for (size_t i = 0 ; i < cols ; i++)
        {
            xm[i][j] = rct::skGen();
            P[i][j] = rct::scalarmultBase(xm[i][j]);
        }
    }
    for (size_t j = 0 ; j < rows ; j++)
    {
        sk[j] = xm[ind][j];
    }
    IIccss = MLSAG_Gen(rct::identity(), P, sk, NULL, NULL, ind, rows);

    return true;
  }

  bool test()
  {
    if (ver)
      MLSAG_Ver(rct::identity(), P, IIccss, rows);
    else
      MLSAG_Gen(rct::identity(), P, sk, NULL, NULL, ind, rows);
    return true;
  }

private:
  rct::keyV sk;
  rct::keyM P;
  size_t ind;
  rct::mgSig IIccss;
};