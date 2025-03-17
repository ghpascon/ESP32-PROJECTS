#include "vars.h"
#include "post_cmd.h"

// class ESP_POST : private post_cmd
class ESP_POST
{
public:
    void is_connected()
    {
        static bool last_connected = false;
        if (last_connected == connected)
            return;
        last_connected = connected;
        if (connected)
        {
            String to_post = "{\"Dispositivo\":\"" + name + "\",\"Tipo\":\"" + String(tipo) + "\",\"Bateria\":0,\"IdCliente\":" + String(id_cliente) + ",\"SurtoEletrico\":\"" + total_surge + "\",\"Dps\":\"" + String(device_state == 0 ? "OK" : (device_state == 1 ? "MANUT" : "INSP_IMEDIATA")) + "\",\"Raios\":\"" + String(qtd_raios) + "\"}";
            make_post(to_post);
        }
    }
};