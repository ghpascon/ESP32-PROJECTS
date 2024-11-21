class check_display
{
public:
    void check_mode()
    {
        if (mode_buttons.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_buttons.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            mode = value;
            Serial.println("Mode: " + String(mode));
            Lcm.changePicId(mode);
        }
    }

    void check_retry()
    {
        if (retry_buttons.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = retry_buttons.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (retry > retry_interval[0])
                    retry--;
            }
            if (value == 1)
            {
                if (retry < retry_interval[1])
                    retry++;
            }
            Serial.println("Retry: " + String(retry));
            retry_display.write(retry);
        }
    }

    void check_speed()
    {
        if (speed_buttons.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = speed_buttons.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (speed > speed_interval[0])
                    speed--;
            }
            if (value == 1)
            {
                if (speed < speed_interval[1])
                    speed++;
            }
            Serial.println("Speed: " + String(speed));
            speed_display.write(speed);
        }
    }

    void check_cfg()
    {
        if (cfg_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = cfg_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                Serial.println("Mode: " + String(mode));
                Lcm.changePicId(mode);
            }
            if (value == 1)
            {
                Serial.println("CONFIG SCREEN");
                Lcm.changePicId(cfg_screen);
            }
        }
    }

    void check_password()
    {
        if (cfg_password.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = cfg_password.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            Serial.println("Password: " + String(value));
            cfg_password.write(0);

            if (value == password)
            {
                Serial.println("Senha correta.");
                Lcm.changePicId(password_ok);
            }
            else
            {
                Serial.println("Senha incorreta.");
                Lcm.changePicId(password_nok);
            }
        }
    }

    void check_ant_cfg()
    {
        mode_1_ant_cfg();
        mode_2_ant_cfg();
        mode_3_ant_cfg();
        mode_4_ant_cfg();
    }

private:
    void mode_1_ant_cfg()
    {
        const byte ant = 0;
        const byte rssi_num = 5;
        if (mode_1_ant_power_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_1_ant_power_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][0] > power_interval[0])
                    ant_cfg[ant][0]--;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][0] < power_interval[1])
                    ant_cfg[ant][0]++;
            }
            Serial.println("Mode: " + String(ant + 1) + " - Ant_power: " + String(ant_cfg[ant][0]));
            mode_1_ant_power_label.write(ant_cfg[ant][0]);
        }

        if (mode_1_ant_rssi_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_1_ant_rssi_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][1] > rssi_interval[0])
                    ant_cfg[ant][1] -= rssi_num;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][1] < rssi_interval[1])
                    ant_cfg[ant][1] += rssi_num;
            }
            Serial.println("Mode: " + String(ant + 1) + " - RSSI: " + String(ant_cfg[ant][1]));
            mode_1_ant_rssi_label.write(ant_cfg[ant][1]);
        }
    }

    void mode_2_ant_cfg()
    {
        const byte ant = 1;
        const byte rssi_num = 5;
        if (mode_2_ant_power_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_2_ant_power_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][0] > power_interval[0])
                    ant_cfg[ant][0]--;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][0] < power_interval[1])
                    ant_cfg[ant][0]++;
            }
            Serial.println("Mode: " + String(ant + 1) + " - Ant_power: " + String(ant_cfg[ant][0]));
            mode_2_ant_power_label.write(ant_cfg[ant][0]);
        }

        if (mode_2_ant_rssi_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_2_ant_rssi_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][1] > rssi_interval[0])
                    ant_cfg[ant][1] -= rssi_num;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][1] < rssi_interval[1])
                    ant_cfg[ant][1] += rssi_num;
            }
            Serial.println("Mode: " + String(ant + 1) + " - RSSI: " + String(ant_cfg[ant][1]));
            mode_2_ant_rssi_label.write(ant_cfg[ant][1]);
        }
    }

    void mode_3_ant_cfg()
    {
        const byte ant = 2;
        const byte rssi_num = 5;
        if (mode_3_ant_power_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_3_ant_power_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][0] > power_interval[0])
                    ant_cfg[ant][0]--;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][0] < power_interval[1])
                    ant_cfg[ant][0]++;
            }
            Serial.println("Mode: " + String(ant + 1) + " - Ant_power: " + String(ant_cfg[ant][0]));
            mode_3_ant_power_label.write(ant_cfg[ant][0]);
        }

        if (mode_3_ant_rssi_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_3_ant_rssi_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][1] > rssi_interval[0])
                    ant_cfg[ant][1] -= rssi_num;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][1] < rssi_interval[1])
                    ant_cfg[ant][1] += rssi_num;
            }
            Serial.println("Mode: " + String(ant + 1) + " - RSSI: " + String(ant_cfg[ant][1]));
            mode_3_ant_rssi_label.write(ant_cfg[ant][1]);
        }
    }

    void mode_4_ant_cfg()
    {
        const byte ant = 3;
        const byte rssi_num = 5;
        if (mode_4_ant_power_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_4_ant_power_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][0] > power_interval[0])
                    ant_cfg[ant][0]--;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][0] < power_interval[1])
                    ant_cfg[ant][0]++;
            }
            Serial.println("Mode: " + String(ant + 1) + " - Ant_power: " + String(ant_cfg[ant][0]));
            mode_4_ant_power_label.write(ant_cfg[ant][0]);
        }

        if (mode_4_ant_rssi_bt.available()) // Verifica se chegou algo no "LcmVar" "NavigationButtons"
        {
            int value = mode_4_ant_rssi_bt.getData(); // Atribui o valor recebido à variável "value"
            if (value == 30806)
                return;
            if (value == 0)
            {
                if (ant_cfg[ant][1] > rssi_interval[0])
                    ant_cfg[ant][1] -= rssi_num;
            }
            if (value == 1)
            {
                if (ant_cfg[ant][1] < rssi_interval[1])
                    ant_cfg[ant][1] += rssi_num;
            }
            Serial.println("Mode: " + String(ant + 1) + " - RSSI: " + String(ant_cfg[ant][1]));
            mode_4_ant_rssi_label.write(ant_cfg[ant][1]);
        }
    }
};
