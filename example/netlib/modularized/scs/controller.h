#ifndef _SCS_CONTROLLER
#define _SCS_CONTROLLER

#include "scsdefs.h"

class Controller {
 public:
    virtual Json::Value post(Request&);
    virtual Json::Value patch(Request&);
    virtual Json::Value put(Request&);
    virtual Json::Value get(Request&);
    virtual Json::Value delete(Request&);
};

#endif // _SCS_CONTROLLER
