#include "scs/scs.h"
#include "userController.hpp"

int main() {
    UserController c;
    SCS::register_controller(&c);
    SCS::run(std::string("0.0.0.0"), std::string("8080"));
    return 0;
}
