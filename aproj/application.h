#pragma once

#include "cmdline.h"
#include "config.h"
#include "connection.h"
#include "connection_manager.h"
#include "router_manager.h"
#include <asio.hpp>
#include <string>

using handler_t = std::function<void(const Request& req, Response& res)>;

class Application {
public:
    // Application& All(const std::string& uri, handler_t handler);
    Application& Get(const std::string& name);
    void Use(const std::string& uri, handler_t handler);
    void Get(const std::string& uri, handler_t handler);

    /// Construct the Application to listen on the specified TCP address and port, and
    /// serve up files from the given directory.
    explicit Application(const std::string& address, const std::string& port, const std::string& doc_root);

    Application();
    ~Application(){};
    int applyCommandLine(int argc, char const* const* argv);

    int Run(int argc, char const* const argv[]);
    void Run();
    inline cmdline::parser& CmdLine() { return cmdline_; }
    /// Run the Application's io_context loop.
    void run();

private:
    /// Perform an asynchronous accept operation.
    void do_accept();

    /// Wait for a request to stop the Application.
    void do_await_stop();

    cmdline::parser cmdline_;

    Config config_;
    /// The io_context used to perform asynchronous operations.
    asio::io_context io_context_;

    /// The signal_set is used to register for process termination notifications.
    asio::signal_set signals_;

    /// Acceptor used to listen for incoming connections.
    asio::ip::tcp::acceptor acceptor_;

    /// The connection manager which owns all live connections.
    connection_manager connection_manager_;

    /// The handler for all incoming requests.
    RouterManager request_handler_;
};
