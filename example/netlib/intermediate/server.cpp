#include <string>
#include <iostream>

#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>

#include "sccdefs.hpp"
#include "handler.hpp"
#include "dispatcher.hpp"

// export BOOST_ROOT=/ust/loca/include/boost
// g++ server.cpp -I$BOOST_ROOT -I. -I$BOOST_ROOT/stage/lib -lboost_system -ljsoncpp -pthread

int main(int argc, char * argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " address port" << std::endl;
        return 1;
    }

    try {
        Handler handler;
        Server::options options(handler);
        options.address(argv[1]).port(argv[2]);
        Server server_(options);
        server_.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
