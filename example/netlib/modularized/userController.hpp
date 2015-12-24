#ifndef _SCS_EXAMPLE_USER_CONTROLLER
#define _SCS_EXAMPLE_USER_CONTROLLER

#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>
#include "scs/scsdefs.h"
#include "scs/controller.h"

//typedef boost::network::http::server::request Request;

class UserController: public Controller {
 public:
    UserController() {}
    static std::string URLS[] = {"/user", "/user/"};
    status std::string METHODS[] = {"get"};
    Json::value get(const Request &request) {
        std::string ip = source(request);
        Json::Value obj(request.body);
        return obj;
    }
};

#endif
