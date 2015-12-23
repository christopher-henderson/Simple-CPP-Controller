#ifndef _SCC_EXAMPLE_USER_CONTROLLER
#define _SCC_EXAMPLE_USER_CONTROLLER

#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>
#include "sccdefs.hpp"

//typedef boost::network::http::server::request Request;

class UserController {
 public:
    UserController() {}
    void get(const Request &request) {
        std::string ip = source(request);
        Json::Value obj(request.body);
        // std::cout << (std::string) query(request) << std::endl;
        std::cout << obj.toStyledString() << std::endl;
    }
};

#endif
