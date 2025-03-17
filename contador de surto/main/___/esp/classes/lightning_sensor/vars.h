#include <Wire.h>
#include <SparkFun_AS3935.h>

#define AS3935_ADDR 0x03
#define INDOOR 0x12
#define OUTDOOR 0xE
#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

SparkFun_AS3935 lightning(AS3935_ADDR);
extern byte lightning_distance;
bool sensor_found = false;