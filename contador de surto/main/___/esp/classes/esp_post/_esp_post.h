#include "vars.h"
#include "post_cmd.h"

class ESP_POST
{
public:
    void is_connected()
    {
        static bool last_connected = false;

        if (last_connected == connected)
            return;
        last_connected = connected;
        online = connected;
        if (connected)
        {
            api_status = "20";
        }
        else
        {
            api_status = "21";
        }
    }

    void post(String to_post)
    {
        if (!connected)
            return;

        make_post(to_post);
    }
};