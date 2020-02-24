#pragma once

#include <array>
#include <memory>
#include <asio.hpp>
#include "response.h"
#include "request.h"
#include "router_manager.h"
#include "request_parser.h"

class connection_manager;

/// Represents a single connection from a client.
class connection
  : public std::enable_shared_from_this<connection>
{
public:
  connection(const connection&) = delete;
  connection& operator=(const connection&) = delete;

  /// Construct a connection with the given socket.
  explicit connection(asio::ip::tcp::socket socket,
      connection_manager& manager, RouterManager& handler);

  /// Start the first asynchronous operation for the connection.
  void start();

  /// Stop all asynchronous operations associated with the connection.
  void stop();

private:
  /// Perform an asynchronous read operation.
  void do_read();

  /// Perform an asynchronous write operation.
  void do_write();

  /// Socket for the connection.
  asio::ip::tcp::socket socket_;

  /// The manager for this connection.
  connection_manager& connection_manager_;

  /// The handler used to process the incoming request.
  RouterManager& request_handler_;

  /// Buffer for incoming data.
  std::array<char, 8192> buffer_;

  /// The incoming request.
  Request request_;

  /// The parser for the incoming request.
  RequestParser request_parser_;

  /// The Response to be sent back to the client.
  Response reply_;
};

using connection_sptr_t = std::shared_ptr<connection>;


