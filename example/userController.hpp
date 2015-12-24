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
    UserController() {
        URLS.push_back("/user");
        URLS.push_back("/user/");
        METHODS.push_back("get");
        METHODS.push_back("post");
    }
    Json::Value get(Request &request) {
        Json::Value obj("YOU'RE ABOUT TO GET A REAL COOL THING!\n");
        return obj;
    }
    Json::Value post(Request &request) {
        Json::Value obj("YOU JUST MADE A REAL COOL THING!\n");
        return obj;
    }
    std::vector<std::string> getUrls() {return URLS;};
    std::vector<std::string> getMethods() {return METHODS;};
 private:
    std::vector<std::string> URLS;
    std::vector<std::string> METHODS;
};

#endif
