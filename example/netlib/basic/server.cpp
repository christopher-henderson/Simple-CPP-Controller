#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>

// export BOOST_ROOT=/ust/loca/include/boost
// g++ server.cpp -I$BOOST_ROOT -I. -I$BOOST_ROOT/stage/lib -lboost_system -ljsoncpp -pthread

namespace http = boost::network::http;

struct hello_world;
typedef http::server<hello_world> server;

struct hello_world {
    void operator() (server::request const &request, server::response &response) {

        response = server::response::stock_reply(
            server::response::ok,
            std::string("Hello, ") + ip + "!" + "\n");
    }
    void log(std::string dontcare){std::cout << dontcare << std::endl;}
};

int
main(int argc, char * argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " address port" << std::endl;
        return 1;
    }

    try {
        hello_world handler;
        server::options options(handler);
        options.address(argv[1]).port(argv[2]);
        server server_(options);
        server_.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
