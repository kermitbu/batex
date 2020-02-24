#pragma once

#include <string>

#include "router.h"

struct Response;
struct Request;

/// The common handler for all incoming requests.
class RouterManager
{
public:
  RouterManager(const RouterManager&) = delete;
  RouterManager& operator=(const RouterManager&) = delete;
  RouterManager(){};
  /// Construct with a directory containing files to be served.
  explicit RouterManager(const std::string& doc_root);

  void AddRoute(const std::string& pattern, handler_t handler);

  /// Handle a request and produce a Response.
  void handle_request(const Request& req, Response& res);
  void handle_request2(const Request& req, Response& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;
  std::vector<Router> router_list_;
  std::unordered_map<std::string, handler_t> route_dict_;
  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

