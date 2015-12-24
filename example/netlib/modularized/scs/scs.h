#ifndef _SCS
#define _SCS

#include <string>
#include "scsdefs.h"
#include "controller.h"
#include "dispatcher.h"

namespace SCS {

    void run(const std::string&, const std::string&);
    void _event_loop(const Server&);

    void register(Controller controller) {
        Dispatcher::register(controller);
    }

    void run(const std::string& hostname, const std::string& port) {
        Handler handler;
        Server::options options(handler).
            address(hostname).
            port(port);
        Server server(options);
        _event_loop(server);
    }

    void _event_loop(const Server& server) {
        try {
            server.run();
        } catch (std::exception &error) {
            std::cerr << e.what() << std::endl;
        }
    }

    // void set_logging_level();

}

#endif