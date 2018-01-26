// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

/*!
 * \file electrum-words.h
 * 
 * \brief Mnemonic seed generation and wallet restoration from them.
 * 
 * This file and its cpp file are for translating Electrum-style word lists
 * into their equivalent byte representations for cross-compatibility with
 * that method of "backing up" one's wallet keys.
 */

#ifndef ELECTRUM_WORDS_H
#define ELECTRUM_WORDS_H

#include <string>
#include <cstdint>
#include <map>
#include "crypto/crypto.h"  // for declaration of crypto::secret_key

/*!
 * \namespace crypto
 * 
 * \brief crypto namespace.
 */
namespace crypto
{
  /*!
   * \namespace crypto::ElectrumWords
   * 
   * \brief Mnemonic seed word generation and wallet restoration helper functions.
   */
  namespace ElectrumWords
  {

    const int seed_length = 24;
    const std::string old_language_name = "EnglishOld";
    /*!
     * \brief Converts seed words to bytes (secret key).
     * \param  words           String containing the words separated by spaces.
     * \param  dst             To put the secret data restored from the words.
     * \param  len             The number of bytes to expect, 0 if unknown
     * \param  duplicate       If true and len is not zero, we accept half the data, and duplicate it
     * \param  language_name   Language of the seed as found gets written here.
     * \return                 false if not a multiple of 3 words, or if word is not in the words list
     */
    bool words_to_bytes(std::string words, std::string& dst, size_t len, bool duplicate,
      std::string &language_name);
    /*!
     * \brief Converts seed words to bytes (secret key).
     * \param  words           String containing the words separated by spaces.
     * \param  dst             To put the secret key restored from the words.
     * \param  language_name   Language of the seed as found gets written here.
     * \return                 false if not a multiple of 3 words, or if word is not in the words list
     */
    bool words_to_bytes(std::string words, crypto::secret_key& dst,
      std::string &language_name);

    /*!
     * \brief Converts bytes to seed words.
     * \param  src           Secret data
     * \param  len           Secret data length in bytes (positive multiples of 4 only)
     * \param  words         Space delimited concatenated words get written here.
     * \param  language_name Seed language name
     * \return               true if successful false if not. Unsuccessful if wrong key size.
     */
    bool bytes_to_words(const char *src, size_t len, std::string& words,
      const std::string &language_name);

    /*!
     * \brief Converts bytes (secret key) to seed words.
     * \param  src           Secret key
     * \param  words         Space delimited concatenated words get written here.
     * \param  language_name Seed language name
     * \return               true if successful false if not. Unsuccessful if wrong key size.
     */
    bool bytes_to_words(const crypto::secret_key& src, std::string& words,
      const std::string &language_name);

    /*!
     * \brief Gets a list of seed languages that are supported.
     * \param languages A vector is set to the list of languages.
     */
    void get_language_list(std::vector<std::string> &languages);

    /*!
     * \brief Tells if the seed passed is an old style seed or not.
     * \param  seed The seed to check (a space delimited concatenated word list)
     * \return      true if the seed passed is a old style seed false if not.
     */
    bool get_is_old_style_seed(std::string seed);
  }
}

#endif
