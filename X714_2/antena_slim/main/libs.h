// arduino libs
#include <Arduino.h>
#include "esp_system.h"
#include "esp_task_wdt.h"

#include <LittleFS.h>

// app
#include "app/pins/_main.h"

#include "app/antena/_main.h"
#include "app/antena/antena_commands.h"

#include "app/tag/_main.h"
#include "app/tag/tag_commands.h"

#include "app/config_file/_main.h"

#include "app/last_packs/_main.h"

#include "app/reader/_main.h"

#include "app/serial_commands/_main.h"

#include "app/ethernet/_main.h"

#include "app/web_server/_main.h"
