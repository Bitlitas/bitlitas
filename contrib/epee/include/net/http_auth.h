// Copyright (c) 2018, Bitlitas
// All rights reserved.

#pragma once

#include <boost/optional/optional.hpp>
#include <boost/utility/string_ref.hpp>
#include <cstdint>
#include <functional>
#include <string>
#include <utility>
#include "wipeable_string.h"
#include "http_base.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "net.http"

namespace epee
{
namespace net_utils
{
  namespace http
  {
    struct login
    {
      login() : username(), password() {}
      login(std::string username_, wipeable_string password_)
        : username(std::move(username_)), password(std::move(password_))
      {}

      std::string username;
      wipeable_string password;
    };

    //! Implements RFC 2617 digest auth. Digests from RFC 7616 can be added.
    class http_server_auth
    {
    public:
      struct session
      {
        session(login credentials_)
          : credentials(std::move(credentials_)), nonce(), counter(0)
        {}

        login credentials;
        std::string nonce;
        std::uint32_t counter;
      };

      http_server_auth() : user(), rng() {}
      http_server_auth(login credentials, std::function<void(size_t, uint8_t*)> r);

      //! \return Auth response, or `boost::none` iff `request` had valid auth.
      boost::optional<http_response_info> get_response(const http_request_info& request)
      {
        if (user)
          return do_get_response(request);
        return boost::none;
      }

    private:
      boost::optional<http_response_info> do_get_response(const http_request_info& request);

      boost::optional<session> user;

      std::function<void(size_t, uint8_t*)> rng;
    };

    //! Implements RFC 2617 digest auth. Digests from RFC 7616 can be added.
    class http_client_auth
    {
    public:
      enum status : std::uint8_t { kSuccess = 0, kBadPassword, kParseFailure };

      struct session
      {
        session(login credentials_)
          : credentials(std::move(credentials_)), server(), counter(0)
        {}

        struct keys
        {
          using algorithm =
            std::function<std::string(const session&, boost::string_ref, boost::string_ref)>;

          keys() : nonce(), opaque(), realm(), generator() {}
          keys(std::string nonce_, std::string opaque_, std::string realm_, algorithm generator_)
            : nonce(std::move(nonce_))
            , opaque(std::move(opaque_))
            , realm(std::move(realm_))
            , generator(std::move(generator_))
          {}

          std::string nonce;
          std::string opaque;
          std::string realm;
          algorithm generator;
        };

        login credentials;
        keys server;
        std::uint32_t counter;
      };

      http_client_auth() : user() {}
      http_client_auth(login credentials);

      /*!
        Clients receiving a 401 response code from the server should call this
        function to process the server auth. Then, before every client request,
        `get_auth_field()` should be called to retrieve the newest
        authorization request.

        \return `kBadPassword` if client will never be able to authenticate,
          `kParseFailure` if all server authentication responses were invalid,
          and `kSuccess` if `get_auth_field` is ready to generate authorization
          fields.
      */
      status handle_401(const http_response_info& response)
      {
        if (user)
          return do_handle_401(response);
        return kBadPassword;
      }

      /*!
        After calling `handle_401`, clients should call this function to
        generate an authentication field for every request.

        \return A HTTP "Authorization" field if `handle_401(...)` previously
          returned `kSuccess`.
      */
      boost::optional<std::pair<std::string, std::string>> get_auth_field(
        const boost::string_ref method, const boost::string_ref uri)
      {
        if (user)
          return do_get_auth_field(method, uri);
        return boost::none;
      }

    private:
      status do_handle_401(const http_response_info&);
      boost::optional<std::pair<std::string, std::string>> do_get_auth_field(boost::string_ref, boost::string_ref);

      boost::optional<session> user;
    };
  }
}
}
