#include "../scs/scs.h"
#include "userController.hpp"

/**
EXAMPLE:
 Build and Run:
     $ brew install cpp-netlib
     $ export BOOST_ROOT=/usr/local/include
     $ g++ server.cpp -I$BOOST_ROOT -I. -I$BOOST_ROOT/stage/lib -L/usr/local/lib -lboost_system -ljsoncpp -pthread
     $ ./a.out

 Test:
     $ curl -X POST http://localhost:8080/user -d '{"this": "is some object"}'
     YOU JUST MADE A REAL COOL THING!
     $ curl -X GET http://localhost:8080/user
     YOU'RE ABOUT TO GET A REAL COOL THING!
*/

int main() {
    UserController c;
    SCS::register_controller(&c);
    SCS::run(std::string("0.0.0.0"), std::string("8080"));
    return 0;
}
