#include "libs.h"
#include "vars.h"
#include "commands_functions.h"

#include "web_server_config.h"
#include "connections.h"
#include "http_post.h"

class WEB_SERVER_ESP : private web_server_config, public connections, public http_post
{
public:
    void setup()
    {
        server_config();
    }
};