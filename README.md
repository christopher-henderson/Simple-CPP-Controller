# Simple-CPP-Server

## Purpose

## Goal

```yaml
---
  server: 
    source_path: "~/repos/MediaServer/src"
    event_loop: 
      destination: "main/server.h"
      pthreads: false
    target_controllers: 
      - 
        file: "controllers/user.h"
        class: "User"
        url_mapping: "/user"
```

```C++
#include <jsoncpp/json/json.h>
#include "UserController.h"

class User : public UserController {
  public Json::Value get(const Request&);
};
```

## Proposal
