#ifndef _SCS_TYPE_DEFS
#define _SCS_TYPE_DEFS

#include <boost/network/protocol/http/server.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

struct Handler;
typedef boost::network::http::server<Handler> Server;
typedef Server::request Request;
typedef Server::response Response;

#endif
