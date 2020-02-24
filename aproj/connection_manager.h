#pragma once

#include <set>
#include "connection.h"

/// Manages open connections so that they may be cleanly stopped when the server
/// needs to shut down.
class connection_manager
{
public:
  connection_manager(const connection_manager&) = delete;
  connection_manager& operator=(const connection_manager&) = delete;

  /// Construct a connection manager.
  connection_manager();

  /// Add the specified connection to the manager and start it.
  void start(connection_sptr_t c);

  /// Stop the specified connection.
  void stop(connection_sptr_t c);

  /// Stop all connections.
  void stop_all();

private:
  /// The managed connections.
  std::set<connection_sptr_t> connections_;
};
