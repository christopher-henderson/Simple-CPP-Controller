# Simple-CPP-Server

## Purpose

## Dependencies
SCS depends on cpp-netlib which, in turn, depends on boost. These are very popular libraries and should be readily found in your OS's package manager of choice.

## Example
Given the following project hierarchy:
```
project
│   README.md
│   configure   
│
└───src
    │   server.cpp
    │   userController.hpp
    │
    ├───scs
    │   │   ...
    │
```
### src/server.cpp
```C++
#include "scs/scs.h"
#include "userController.hpp"

int main() {
    UserController c;
    SCS::register_controller(&c);
    SCS::run(std::string("0.0.0.0"), std::string("8080"));
    return 0;
}
```

### src/userController.hpp
```C++
#ifndef _SCS_EXAMPLE_USER_CONTROLLER
#define _SCS_EXAMPLE_USER_CONTROLLER

#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>
#include "scs/scsdefs.h"
#include "scs/controller.h";

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
```
