#include "router_manager.h"
#include "mime_types.h"
#include "request.h"
#include "response.h"
#include "spdlog/spdlog.h"
#include "tools.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

RouterManager::RouterManager( const std::string& doc_root ) : doc_root_( doc_root ) {}

void RouterManager::handle_request( const Request& req, Response& res ) {
    auto begin_clock = std::chrono::steady_clock::now();
    std::string request_path;
    if ( !url_decode( req.uri, request_path ) ) {
        res = Response::stock_reply( Response::bad_request );
        return;
    }

    // Request path must be absolute and not contain "..".
    if ( request_path.empty() || request_path[ 0 ] != '/' || request_path.find( ".." ) != std::string::npos ) {
        res = Response::stock_reply( Response::bad_request );
        return;
    }

    auto route = route_dict_.find( request_path );
    if ( route != route_dict_.end() ) {
        route->second( req, res );
    } else {

    // Open the file to send back.
    std::string full_path = doc_root_ + request_path;
    std::ifstream is( full_path.c_str(), std::ios::in | std::ios::binary );
    if ( !is ) {
        res = Response::stock_reply( Response::not_found );
        return;
    }

    spdlog::get( "lisa" )->info( "request_path: {}", request_path );

    for ( auto&& i : req.headers_ ) {
        spdlog::get( "lisa" )->info( "header: {} : {}", i.name, i.value );
    }

    // Fill out the Response to be sent to the client.
    res.status = Response::ok;
    char buf[ 512 ];
    while ( is.read( buf, sizeof( buf ) ).gcount() > 0 )
        res.content.append( buf, is.gcount() );
    res.headers_.resize( 2 );
    res.headers_[ 0 ].name = "Content-Length";
    res.headers_[ 0 ].value = std::to_string( res.content.size() );
    res.headers_[ 1 ].name = "Content-Type";
    res.headers_[ 1 ].value = mime_types::extension_to_type( tools::parse_file_extension( request_path ) );
}

    auto end_clock = std::chrono::steady_clock::now();

    spdlog::get( "lisa" )->info(
        "{} {} {} {}us", req.method, request_path, res.status,
        std::chrono::duration_cast< std::chrono::microseconds >( end_clock - begin_clock ).count() );
    return;
}

void RouterManager::AddRoute( const std::string& pattern, handler_t handler ) {
    route_dict_.insert( {pattern, handler} );
}

bool RouterManager::url_decode( const std::string& in, std::string& out ) {
    out.clear();
    out.reserve( in.size() );
    for ( std::size_t i = 0; i < in.size(); ++i ) {
        if ( in[ i ] == '%' ) {
            if ( i + 3 <= in.size() ) {
                int value = 0;
                std::istringstream is( in.substr( i + 1, 2 ) );
                if ( is >> std::hex >> value ) {
                    out += static_cast< char >( value );
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if ( in[ i ] == '+' ) {
            out += ' ';
        } else {
            out += in[ i ];
        }
    }
    return true;
}
