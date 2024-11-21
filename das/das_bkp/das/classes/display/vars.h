#include <UnicViewAD.h>
LCM Lcm(Serial2);

LcmVar mode_buttons(0);
extern byte mode;

LcmVar retry_buttons(1);
LcmVar retry_display(2);
extern byte retry;
extern const byte retry_interval[];

LcmVar speed_buttons(3);
LcmVar speed_display(4);
extern byte speed;
extern const byte speed_interval[];

LcmVar cfg_bt(5);
LcmVar cfg_password(6);
extern int password;

LcmVar mode_1_ant_power_bt(7);
LcmVar mode_1_ant_power_label(8);
LcmVar mode_1_ant_rssi_bt(9);
LcmVar mode_1_ant_rssi_label(10);

LcmVar mode_2_ant_power_bt(11);
LcmVar mode_2_ant_power_label(12);
LcmVar mode_2_ant_rssi_bt(13);
LcmVar mode_2_ant_rssi_label(14);

LcmVar mode_3_ant_power_bt(15);
LcmVar mode_3_ant_power_label(16);
LcmVar mode_3_ant_rssi_bt(17);
LcmVar mode_3_ant_rssi_label(18);

LcmVar mode_4_ant_power_bt(19);
LcmVar mode_4_ant_power_label(20);
LcmVar mode_4_ant_rssi_bt(21);
LcmVar mode_4_ant_rssi_label(22);

extern byte ant_cfg[][2];
extern const byte power_interval[];
extern const byte rssi_interval[];

extern ESP_POST esp_post;
extern bool posted;
extern bool connected;

const byte device_num = 4;
String device[device_num] = {
    "MODE1",
    "MODE2",
    "MODE3",
    "MODE4"};

String commands[2] = {"StartDevice", "StopDevice"};