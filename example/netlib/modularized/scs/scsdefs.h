#ifndef _SCS_TYPE_DEFS
#define _SCS_TYPE_DEFS

#include <boost/network/protocol/http/server.hpp>

struct Handler;
typedef boost::unordered_map<std::string, Controller> ControllerMap;
typedef boost::unordered_set<Controller*> ControllerSet;
typedef boost::unordered_map<std::string, ControllerSet> MethodMap;
typedef boost::network::http::server<Handler> Server;
typedef Server::request Request;
typedef Server::response Response;

#endif
