#ifndef _SCS_DISPATCHER_H
#define _SCS_DISPATCHER_H

#include <string>
#include <iostream>
#include <stdlib.h>

#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>
#include <boost/network/protocol/http/server.hpp>
#include <jsoncpp/json/json.h>

#include "scsdefs.h"
#include "controller.h"

typedef boost::unordered_map<std::string, Controller*> ControllerMap;
typedef boost::unordered_set<Controller*> ControllerSet;
typedef boost::unordered_map<std::string, ControllerSet> MethodMap;
typedef std::vector<std::string>::iterator iter;

class Dispatcher {
 public:
    static Response handle(Request& request);
    static void register_controller(Controller* controller);

 private:
    static Response dispatch(Request&, Controller*);
    static bool supported_method(Request&, Controller*);
    static ControllerMap controllers;
    static MethodMap methods;
};

Response Dispatcher::handle(Request &request) {
    Controller* controller;
    try {
        controller = controllers.at(request.destination);
    } catch (std::out_of_range &error) {
        // Return 404;
        return Response::stock_reply(Response::not_found, "");
    }
    if (!Dispatcher::supported_method(request, controller)) {
        // return 403;
        return Response::stock_reply(Response::forbidden, "");
    }
    return Dispatcher::dispatch(request, controller);
}

void Dispatcher::register_controller(Controller* controller) {
    std::string mapping;
    std::string method;
    std::vector<std::string> urls = controller->getUrls();
    std::vector<std::string> methods = controller->getMethods();
    for (iter iterator = urls.begin(); iterator != urls.end(); iterator++) {
        mapping = *iterator;
        if (Dispatcher::controllers.count(mapping) > 0) {
            // Log warning of mapping override.
        }
        Dispatcher::controllers[mapping] = controller;
    }
    for (iter iterator = methods.begin(); iterator != methods.end(); iterator++) {
        method = boost::to_upper_copy(*iterator);
        if (!Dispatcher::methods.at(method).insert(controller).second) {
            // Log warning about failure to insert method support.
        }
    }
}

Response Dispatcher::dispatch(Request& request, Controller* controller) {
    std::string method = request.method;
    Json::Value data;
    Response::status_type status_code;
    if (method.compare("GET") == 0) {
        data = controller->get(request);
        status_code = Response::ok;
    }
    else if (method.compare("POST") == 0) {
        data = controller->post(request);
        status_code = Response::created;
    }
    else if (method.compare("PUT") == 0) {
        data = controller->put(request);
        status_code = Response::ok;
    }
    else if (method.compare("PATCH") == 0) {
        data = controller->patch(request);
        status_code = Response::ok;
    }
    else if (method.compare("DELETE") == 0) {
        data = controller->_delete(request);
        status_code = Response::ok;
    } else {
        status_code = Response::forbidden;
    }
    return Response::stock_reply(status_code, data.asString());
}

bool Dispatcher::supported_method(Request& request, Controller* controller) {
    try {
        return methods[request.method].count(controller) > 0;
    } catch (std::out_of_range &error) {
        // This would be odd. Log this.
        return false;
    }
}

ControllerMap MakeControllerMap() {
    ControllerMap controllers;
    return controllers;
}

MethodMap MakeMethodMap() {
    MethodMap methods;
    methods["GET"] = ControllerSet();
    methods["PUT"] = ControllerSet();
    methods["PATCH"] = ControllerSet();
    methods["POST"] = ControllerSet();
    methods["DELETE"] = ControllerSet();
    return methods;
}

MethodMap Dispatcher::methods = MakeMethodMap();
ControllerMap Dispatcher::controllers = MakeControllerMap();

#endif // _SCS_DISPATCHER_H
