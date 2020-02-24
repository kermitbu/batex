#include "application.h"
#include <signal.h>
#include <utility>
#include "spdlog/spdlog.h"

Application::Application()
    : io_context_( 1 ), signals_( io_context_ ), acceptor_( io_context_ ), connection_manager_() 
    ,request_handler_("../templates")
    {
    // todo 需通过开关控制
    signals_.add( SIGINT );
    signals_.add( SIGTERM );
    signals_.add( SIGQUIT );

    static std::once_flag flag_s;
    std::call_once(flag_s, [](){ 
        auto log = spdlog::stdout_color_mt("lisa");
        log->set_pattern("%v");
         });
}

int Application::applyCommandLine( int argc, char const* const* argv ) {
    cmdline_.add< std::string >( "host", 'h', "host name", false, "127.0.0.1" );
    cmdline_.add< int >( "port", 'p', "port number", false, 3000, cmdline::range( 1, 65535 ) );
    cmdline_.add< std::string >( "root", 'r', "doc root", false, "./templates" );
    cmdline_.add( "help", 0, "print this message" );
    cmdline_.set_program_name( "lisa" );

    bool ok = cmdline_.parse( argc, argv );
    if ( cmdline_.exist( "help" ) ) {
        std::cerr << cmdline_.usage();
        return 0;
    }

    if ( !ok ) {
        std::cerr << cmdline_.error() << std::endl << cmdline_.usage();
        return -1;
    }

    if (cmdline_.exist("host") ){
        config_.address_ = cmdline_.get<std::string>("host");
    } else {
        config_.address_ = "127.0.0.1";
    }
    if (cmdline_.exist("port") ){
        config_.port_ = std::to_string(cmdline_.get<int>("port"));
    } else {
        config_.port_ = "5000";
    }

    std::cout << config_.address_ << ":" << config_.port_  << std::endl;

    return 0;
}

int Application::Run( int argc, char const* const argv[] ) {
    if ( applyCommandLine( argc, argv ) == 0 ) {
        Run();
        return 0;
    }
    return -1;
}

void Application::Run() {
    do_await_stop();
    asio::ip::tcp::resolver resolver( io_context_ );
    asio::ip::tcp::endpoint endpoint = *resolver.resolve( config_.address_, config_.port_ ).begin();
    acceptor_.open( endpoint.protocol() );
    acceptor_.set_option( asio::ip::tcp::acceptor::reuse_address( true ) );
    acceptor_.bind( endpoint );
    acceptor_.listen();
    do_accept();
    io_context_.run();
}

void Application::do_accept() {
    acceptor_.async_accept( [this]( std::error_code ec, asio::ip::tcp::socket socket ) {
        // Check whether the Application was stopped by a signal before this
        // completion handler had a chance to run.
        if ( !acceptor_.is_open() ) {
            return;
        }

        if ( !ec ) {
            connection_manager_.start(
                std::make_shared< connection >( std::move( socket ), connection_manager_, request_handler_ ) );
        }

        do_accept();
    } );
}

void Application::do_await_stop() {
    signals_.async_wait( [this]( std::error_code /*ec*/, int /*signo*/ ) {
        // The Application is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_context::run()
        // call will exit.
        acceptor_.close();
        connection_manager_.stop_all();
    } );
}

void Application::Use(const std::string& uri, handler_t handler) {
//    request_handler_.AddRoute(uri, handler);
};

void Application::Get(const std::string& uri, handler_t handler) {
    request_handler_.AddRoute(uri, handler);
};