#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard my_keyboard;
USBCDC my_usb;

#define tx_reader_module 13
#define rx_reader_module 14

extern bool keyboard;
extern bool simple_send;
