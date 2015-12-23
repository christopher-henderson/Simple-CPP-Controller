#ifndef _SCC_HANDLER
#define _SCC_HANDLER

#include "sccdefs.hpp"
#include "dispatcher.hpp"

struct Handler {
    void operator() (Request const &request, Response &response) {
        std::string ip = source(request);
        Dispatcher::handle(request);
        response = Response::stock_reply(
            Response::ok,
            std::string("Hello, ") + ip + "!" + "\n");
    }
    void log(std::string dontcare){std::cout << dontcare << std::endl;}
};

#endif