#include "api.h"
#include "power.h"

void setup() {

   /* Test for the first couple RVR commands */
   init_port();

   wake();

   uint8_t * hello = echo("Hello World", strlen("Hello World"));
   Serial.print("Sent 'Hello World' and got back '");
   Serial.print((char*)hello); Serial.println("'");
   fallasleep();

}

void loop() {
}
