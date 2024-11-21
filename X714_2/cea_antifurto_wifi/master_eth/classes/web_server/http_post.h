#include "post_cmd.h"

class http_post
{
public:
    void post()
    {
        const int post_time = 30000;
        static unsigned long current_post_time = -post_time;

        if (millis() - current_post_time < post_time)
            return;

        if (!eth_connected)
            return;

        if (posted)
            return;

        current_post_time = millis();

        make_post(get_json_commands());
    }
};