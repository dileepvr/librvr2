#include "power.h"
#include "connection.h"

void setup() {

   /* Test for the first couple RVR commands */
   init_port();

   wake();

   byte * btname = get_bluetooth_advertising_name();
   Serial.print("BT name is ");
   Serial.println((char*)btname);

   close_port();
}

void loop() {
}
