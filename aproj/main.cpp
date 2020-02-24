#include "application.h"
#include "spdlog/spdlog.h"

int main( int argc, char* argv[] ) {
     Application app;

    app.Use("/", [](const Request& req, Response& res){
        spdlog::get( "lisa" )->info( "{} {}", req.method, req.uri);
    });

    app.Get("/", [](const Request& req, Response& res){
        res.Send("HelloWorld");
    });

    return app.Run( argc, argv );
}