#pragma once


#include <string>
#include <vector>
#include <asio.hpp>
#include "header.h"
#include <unordered_map>
#include "router.h"
/// A Response to be sent to a client.

struct Response
{
  /// The status of the Response.
  enum status_type
  {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  } status;

  /// The headers to be included in the Response.
  std::vector<header> headers_;


  /// The content to be sent in the Response.
  std::string content;

  /// Convert the Response into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the Response object must remain valid and
  /// not be changed until the write operation has completed.
  std::vector<asio::const_buffer> to_buffers();

  /// Get a stock Response.
  static Response stock_reply(status_type status);


  ///////////////////////////



   void append(std::initializer_list<std::string>) {}

void attachment() {}
void attachment(const std::string& value) {}

struct Property{
  std::string key;
  std::string value;
};

void cookie(const std::string& name, const std::string& value, std::initializer_list<Property> properties) {}

void clearCookie(const std::string& name, std::initializer_list<Property> properties) {}

void Download() {}
Response& End() {return *this;}
Response& Format() {  return *this;}

std::string Get(const std::string &mime) {return "";}
Response& Json(const std::string &jsonstr) {return *this;}
Response& Jsonp(){return *this;}
Response& Links() {return *this;}
Response& Location(const std::string& path){return *this;}
Response& Redirect(const std::string& path) {return *this;}
Response& Redirect(int16_t status, const std::string& path) {return *this;}
Response& Render() {return *this;};
void Send(const std::string& value);
Response& SendFile(const std::string& name, std::initializer_list<Property> properties) {return *this;}
Response& SendStatus(uint16_t status){return *this;}

Response& Set(const std::string& name, std::string value){return *this;}
Response& Set(std::initializer_list<Property> properties){return *this;}

Response& Status(uint16_t status){return *this;}
Response& Type(std::string t){return *this;}
Response& Vary(const std::string& name, std::string& value) {return *this;}

 private:
std::string app;
bool headers_sent;
std::unordered_map<std::string, std::string> locals;
};

