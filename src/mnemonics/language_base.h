// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

/*!
 * \file language_base.h
 * 
 * \brief Language Base class for Polymorphism.
 */

#ifndef LANGUAGE_BASE_H
#define LANGUAGE_BASE_H

#include <vector>
#include <unordered_map>
#include <string>
#include "misc_log_ex.h"

/*!
 * \namespace Language
 * \brief Mnemonic language related namespace.
 */
namespace Language
{
  /*!
   * \brief Returns a string made of (at most) the first count characters in s.
   *        Assumes well formedness. No check is made for this.
   * \param  s               The string from which to return the first count characters.
   * \param  count           How many characters to return.
   * \return                 A string consisting of the first count characters in s.
   */
  inline std::string utf8prefix(const std::string &s, size_t count)
  {
    std::string prefix = "";
    const char *ptr = s.c_str();
    while (count-- && *ptr)
    {
      prefix += *ptr++;
      while (((*ptr) & 0xc0) == 0x80)
        prefix += *ptr++;
    }
    return prefix;
  }

  /*!
   * \class Base
   * \brief A base language class which all languages have to inherit from for
   * Polymorphism.
   */
  class Base
  {
  protected:
    enum {
      ALLOW_SHORT_WORDS = 1<<0,
      ALLOW_DUPLICATE_PREFIXES = 1<<1,
    };
    const std::vector<std::string> word_list; /*!< A pointer to the array of words */
    std::unordered_map<std::string, uint32_t> word_map; /*!< hash table to find word's index */
    std::unordered_map<std::string, uint32_t> trimmed_word_map; /*!< hash table to find word's trimmed index */
    std::string language_name; /*!< Name of language */
    uint32_t unique_prefix_length; /*!< Number of unique starting characters to trim the wordlist to when matching */
    /*!
     * \brief Populates the word maps after the list is ready.
     */
    void populate_maps(uint32_t flags = 0)
    {
      int ii;
      std::vector<std::string>::const_iterator it;
      if (word_list.size () != 1626)
        throw std::runtime_error("Wrong word list length for " + language_name);
      for (it = word_list.begin(), ii = 0; it != word_list.end(); it++, ii++)
      {
        word_map[*it] = ii;
        if ((*it).size() < unique_prefix_length)
        {
          if (flags & ALLOW_SHORT_WORDS)
            MWARNING(language_name << " word '" << *it << "' is shorter than its prefix length, " << unique_prefix_length);
          else
            throw std::runtime_error("Too short word in " + language_name + " word list: " + *it);
        }
        std::string trimmed;
        if (it->length() > unique_prefix_length)
        {
          trimmed = utf8prefix(*it, unique_prefix_length);
        }
        else
        {
          trimmed = *it;
        }
        if (trimmed_word_map.find(trimmed) != trimmed_word_map.end())
        {
          if (flags & ALLOW_DUPLICATE_PREFIXES)
            MWARNING("Duplicate prefix in " << language_name << " word list: " << trimmed);
          else
            throw std::runtime_error("Duplicate prefix in " + language_name + " word list: " + trimmed);
        }
        trimmed_word_map[trimmed] = ii;
      }
    }
  public:
    Base(const char *language_name, const std::vector<std::string> &words, uint32_t prefix_length):
      word_list(words),
      unique_prefix_length(prefix_length),
      language_name(language_name)
    {
    }
    virtual ~Base()
    {
    }
    /*!
     * \brief Returns a pointer to the word list.
     * \return A pointer to the word list.
     */
    const std::vector<std::string>& get_word_list() const
    {
      return word_list;
    }
    /*!
     * \brief Returns a pointer to the word map.
     * \return A pointer to the word map.
     */
    const std::unordered_map<std::string, uint32_t>& get_word_map() const
    {
      return word_map;
    }
    /*!
     * \brief Returns a pointer to the trimmed word map.
     * \return A pointer to the trimmed word map.
     */
    const std::unordered_map<std::string, uint32_t>& get_trimmed_word_map() const
    {
      return trimmed_word_map;
    }
    /*!
     * \brief Returns the name of the language.
     * \return Name of the language.
     */
    const std::string &get_language_name() const
    {
      return language_name;
    }
    /*!
     * \brief Returns the number of unique starting characters to be used for matching.
     * \return Number of unique starting characters.
     */
    uint32_t get_unique_prefix_length() const
    {
      return unique_prefix_length;
    }
  };
}

#endif