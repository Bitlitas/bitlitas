// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "include_base_utils.h"
#include "file_io_utils.h"
#include "net/http_client.h"
#include "fuzzer.h"

class dummy_client
{
public:
  bool connect(const std::string& addr, int port, std::chrono::milliseconds timeout, bool ssl = false, const std::string& bind_ip = "0.0.0.0") { return true; }
  bool connect(const std::string& addr, const std::string& port, std::chrono::milliseconds timeout, bool ssl = false, const std::string& bind_ip = "0.0.0.0") { return true; }
  bool disconnect() { return true; }
  bool send(const std::string& buff, std::chrono::milliseconds timeout) { return true; }
  bool send(const void* data, size_t sz) { return true; }
  bool is_connected() { return true; }
  bool recv(std::string& buff, std::chrono::milliseconds timeout)
  {
    buff = data;
    data.clear();
    return true;
  }

  void set_test_data(const std::string &s) { data = s; }

private:
  std::string data;
};

class HTTPClientFuzzer: public Fuzzer
{
public:
  HTTPClientFuzzer() {}
  virtual int init();
  virtual int run(const std::string &filename);

private:
  epee::net_utils::http::http_simple_client_template<dummy_client> client;
};

int HTTPClientFuzzer::init()
{
  return 0;
}

int HTTPClientFuzzer::run(const std::string &filename)
{
  std::string s;

  if (!epee::file_io_utils::load_file_to_string(filename, s))
  {
    std::cout << "Error: failed to load file " << filename << std::endl;
    return 1;
  }
  try
  {
    client.test(s, std::chrono::milliseconds(1000));
  }
  catch (const std::exception &e)
  {
    std::cerr << "Failed to test http client: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, const char **argv)
{
  HTTPClientFuzzer fuzzer;
  return run_fuzzer(argc, argv, fuzzer);
}

