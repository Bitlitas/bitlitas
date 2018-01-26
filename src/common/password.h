// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <string>
#include <boost/optional/optional.hpp>
#include "wipeable_string.h"

namespace tools
{
  class password_container
  {
  public:
    static constexpr const size_t max_password_size = 1024;

    //! Empty password
    password_container() noexcept;

    //! `password` is used as password
    password_container(std::string&& password) noexcept;

    //! \return A password from stdin TTY prompt or `std::cin` pipe.
    static boost::optional<password_container> prompt(bool verify, const char *mesage = "Password");

    password_container(const password_container&) = delete;
    password_container(password_container&& rhs) = default;

    //! Wipes internal password
    ~password_container() noexcept;

    password_container& operator=(const password_container&) = delete;
    password_container& operator=(password_container&&) = default;

    const epee::wipeable_string &password() const noexcept { return m_password; }

  private:
    epee::wipeable_string m_password;
  };

  struct login
  {
    login() = default;

    /*!
       Extracts username and password from the format `username:password`. A
       blank username or password is allowed. If the `:` character is not
       present, `password_container::prompt` will be called by forwarding the
       `verify` and `message` arguments.

       \param userpass Is "consumed", and the memory contents are wiped.
       \param verify is passed to `password_container::prompt` if necessary.
       \param message is passed to `password_container::prompt` if necessary.

       \return The username and password, or boost::none if
         `password_container::prompt` fails.
     */
    static boost::optional<login> parse(std::string&& userpass, bool verify, const std::function<boost::optional<password_container>(bool)> &prompt);

    login(const login&) = delete;
    login(login&&) = default;
    ~login() = default;
    login& operator=(const login&) = delete;
    login& operator=(login&&) = default;

    std::string username;
    password_container password;
  };
}
