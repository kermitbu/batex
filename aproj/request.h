#pragma once

#include "header.h"
#include <string>
#include <vector>

class Request final {
  public:
#if 0
  void accepts(std::string) {}
  void accepts(std::initializer_list<std::string>) {}
  void acceptsCharsets(std::string& charsets) {}
  void acceptsEncodings(std::string& encoding) {}
  void acceptsLanguages(std::string& language) {}
  std::string get(const std::string& name) {}
  bool is(std::string mime) {}
  std::string param(const std::string& key) {}
 private:
  std::string app;
  std::string baseUrl;
  std::string body;
  std::string cookies;
  std::string fresh;
  std::string hostname;
  std::string ip;
  std::string ips;
  std::string method;
  std::string originalUrl;
  std::string params;
  std::string path;
  std::string protocol;
  std::string query;
  std::string route;
  std::string secure;
  std::string signedCookies;
  std::string stale;
  std::string subdomains;
  std::string xhr;

#endif
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector< header > headers_;
};
