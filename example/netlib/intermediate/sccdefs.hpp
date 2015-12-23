#ifndef _SCC_TYPE_DEFS
#define _SCC_TYPE_DEFS

#include <boost/network/protocol/http/server.hpp>

struct Handler;
typedef boost::network::http::server<Handler> Server;
typedef Server::request Request;
typedef Server::response Response;

#endif