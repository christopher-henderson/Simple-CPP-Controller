#include "UserController.h"

class User: public UserController {
    public:
        Response get(const Request &request) {
            return Response();
        }
};