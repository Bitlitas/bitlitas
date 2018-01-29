// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <boost/algorithm/string.hpp>
#include "misc_log_ex.h"
#include "util.h"
#include "dns_utils.h"
#include "updates.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "updates"

namespace tools
{
  bool check_updates(const std::string &software, const std::string &buildtag, std::string &version, std::string &hash)
  {
    std::vector<std::string> records;
    bool found = false;

    MDEBUG("Checking updates for " << buildtag << " " << software);

    // All four BitlitasPulse domains have DNSSEC on and valid
    static const std::vector<std::string> dns_urls = {
        "updates.bitlitaspulse.org",
        "updates.bitlitaspulse.net",
        "updates.bitlitaspulse.co",
        "updates.bitlitaspulse.se"
    };

    if (!tools::dns_utils::load_txt_records_from_dns(records, dns_urls))
      return false;

    for (const auto& record : records)
    {
      std::vector<std::string> fields;
      boost::split(fields, record, boost::is_any_of(":"));
      if (fields.size() != 4)
      {
        MWARNING("Updates record does not have 4 fields: " << record);
        continue;
      }

      if (software != fields[0] || buildtag != fields[1])
        continue;

      bool alnum = true;
      for (auto c: hash)
        if (!isalnum(c))
          alnum = false;
      if (hash.size() != 64 && !alnum)
      {
        MWARNING("Invalid hash: " << hash);
        continue;
      }

      // use highest version
      if (found)
      {
        int cmp = vercmp(version.c_str(), fields[2].c_str());
        if (cmp > 0)
          continue;
        if (cmp == 0 && hash != fields[3])
          MWARNING("Two matches found for " << software << " version " << version << " on " << buildtag);
      }

      version = fields[2];
      hash = fields[3];

      MINFO("Found new version " << version << " with hash " << hash);
      found = true;
    }
    return found;
  }

  std::string get_update_url(const std::string &software, const std::string &subdir, const std::string &buildtag, const std::string &version, bool user)
  {
    const char *base = user ? "https://downloads.bitlitas.lt/" : "https://updates.bitlitas.lt/";
#ifdef _WIN32
    static const char *extension = strncmp(buildtag.c_str(), "install-", 8) ? ".zip" : ".exe";
#else
    static const char extension[] = ".tar.bz2";
#endif

    std::string url;

    url =  base;
    if (!subdir.empty())
      url += subdir + "/";
    url = url + software + "-" + buildtag + "-v" + version + extension;
    return url;
  }
}
