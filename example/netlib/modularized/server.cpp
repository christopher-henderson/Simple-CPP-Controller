#include "scs/scs.h"
#include "UserController.h"

int main() {
    SCS::register(UserController c);
    SCS::run("0.0.0.0", "8080");
    return 0;
}
