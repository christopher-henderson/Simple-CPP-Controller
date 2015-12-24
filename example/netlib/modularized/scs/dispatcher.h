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


class Dispatcher {
 public:
    static void handle(const Request&);
    static void register(Controller&);

 private:
    static Response dispatch(const Request&, Controller);
    static bool supported_method(const Request&, const Controller&);
    static ControllerMap controllers;
    static MethodMap methods;
};

Response Dispatcher::handle(const Request &request) {
    try {
        Controller controller = controllers.at(request.destination);
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

void Dispatcher::register(Controller &controller) {
    std::string mapping;
    std::string method;
    for (int index=0; index < sizeof(controller.URLS); index++) {
        mapping = controller.URLS[index];
        if (Dispatcher::controllers.count(mapping) > 0) {
            // Log warning of mapping override.
        }
        Dispatcher::controller[mapping] = controller;
    }
    for (int index=0; index < sizeof(controller.METHODS); index++) {
        method = boost::to_upper_copy(controller.METHODS[index]);
        if (!Dispatcher::methods.at(method).insert(&controller)) {
            // Log warning about failure to insert method support.
        }
    }
}

Response Dispatcher::dispatch(const Request& request, Controller controller) {
    std::string method = request.method;
    Json::value data;
    status_type status_code;
    if (method.compare("GET")) {
        data = controller.get(request);
        status_code = Response::ok;
    }
    else if (method.compare("POST")) {
        data = controller.post(request);
        status_code = Response::created;
    }
    else if (method.compare("PUT")) {
        data = controller.put(request);
        status_code = Response::ok;
    }
    else if (method.compare("PATCH")) {
        data = controller.patch(request);
        status_code = Response::ok;
    }
    else if (method.compare("DELETE")) {
        data = controller.delete(request);
        status_code = Response::ok;
    } else {
        status_code = Response::forbidden;
    }
    return Response::stock_reply(status_code, data.asString());
}

bool Dispatcher::supported_method(const Request& request, const Controller& controller) {
    try {
        return methods[request.method].count(&controller) > 0;
    } catch (std::out_of_range &error) {
        // This would be odd. Log this.
        return false;
    }
}

#endif // _SCS_DISPATCHER_H
