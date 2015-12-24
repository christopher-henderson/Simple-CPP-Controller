#ifndef _SCS
#define _SCS

#include <string>
#include "scsdefs.h"
#include "handler.h"
#include "controller.h"
#include "dispatcher.h"

namespace SCS {

    void run(std::string, std::string);
    void _event_loop(Server&);

    void register_controller(Controller* controller) {
        Dispatcher::register_controller(controller);
    }

    void run(std::string hostname, std::string port) {
        Handler handler;
        Server::options options(handler);
        options.address(hostname).port(port);
        Server server(options);
        _event_loop(server);
    }

    void _event_loop(Server& server) {
        try {
            server.run();
        } catch (std::exception &error) {
            std::cerr << error.what() << std::endl;
        }
    }

    // void set_logging_level();

}

#endif