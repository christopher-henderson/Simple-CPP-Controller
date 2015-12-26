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

#define OK(data) (data != NULL) ? Response::ok : Response::forbidden;
#define CREATED(data) (data != NULL) ? Response::created : Response::forbidden;

typedef boost::unordered_map<std::string, Controller*> ControllerMap;
typedef std::vector<std::string>::iterator iter;

class Dispatcher {
 public:
    static Response handle(Request& request);
    static void register_controller(Controller* controller);

 private:
    static Response dispatch(Request&, Controller*);
    static ControllerMap controllers;
};

Response Dispatcher::handle(Request &request) {
    Controller* controller;
    try {
        controller = controllers.at(request.destination);
    } catch (std::out_of_range &error) {
        // Return 404;
        return Response::stock_reply(
            Response::not_found, request.destination + " not found.\n");
    }
    return Dispatcher::dispatch(request, controller);
}

void Dispatcher::register_controller(Controller* controller) {
    std::string mapping;
    std::string method;
    std::vector<std::string> urls = controller->getUrls();
    for (iter iterator = urls.begin(); iterator != urls.end(); iterator++) {
        mapping = *iterator;
        if (Dispatcher::controllers.count(mapping) > 0) {
            // Log warning of mapping override.
        }
        Dispatcher::controllers[mapping] = controller;
    }
}

Response Dispatcher::dispatch(Request& request, Controller* controller) {
    std::string method = request.method;
    Json::Value* data;
    Response::status_type status_code = Response::forbidden;
    if (method.compare("GET") == 0) {
        data = controller->get(request);
        status_code = OK(data);
    } else if (method.compare("POST") == 0) {
        data = controller->post(request);
        status_code = CREATED(data);
    } else if (method.compare("PUT") == 0) {
        data = controller->put(request);
        status_code = OK(data);
    } else if (method.compare("PATCH") == 0) {
        data = controller->patch(request);
        status_code = OK(data);
    } else if (method.compare("DELETE") == 0) {
        data = controller->_delete(request);
        status_code = OK(data);
    } else {
        data = NULL;
        status_code = Response::forbidden;
    }
    if (data == NULL) {
        return Response::stock_reply(
            status_code, request.method + " is not a supported method.\n");
    }
    std::string data_string = data->asString();
    delete data;
    return Response::stock_reply(status_code, data->asString());
}

ControllerMap MakeControllerMap() {
    ControllerMap controllers;
    return controllers;
}

ControllerMap Dispatcher::controllers = MakeControllerMap();

#endif // _SCS_DISPATCHER_H
