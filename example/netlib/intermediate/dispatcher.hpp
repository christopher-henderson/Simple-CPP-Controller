#ifndef _SCC_DISPATCHER
#define _SCC_DISPATCHER

#include <boost/unordered_map.hpp>
#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>
#include "sccdefs.hpp"
#include "userController.hpp"

typedef boost::unordered_map<std::string, UserController*> HandlerHashMap;

namespace Dispatcher {
    void handle(Request const &request) {
        HandlerHashMap handlers;
        handlers["/user"] = new UserController();
        UserController* controller = handlers.at(request.destination);
        controller->get(request);
    }
}

#endif
