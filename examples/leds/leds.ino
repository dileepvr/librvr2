#include "io.h"
#include "power.h"

void setup() {
  byte colors[32];

  init_port();


  wake();
  delay(2000);

  for (int i=0; i<32; i++) colors[i] = 0x00;
  set_all_leds(ALL_LIGHTS, colors);
  delay(1000);
  for (int i=1; i<32; i+=3) colors[i] = 0xFF;
  set_all_leds(ALL_LIGHTS, colors);

  delay(1000);
  for (int i=0; i<32; i++) colors[i] = 0x00;
  set_all_leds(ALL_LIGHTS, colors);
  colors[0] = 0xFF;
  set_all_leds(LEFT_HEADLIGHT_GROUP, colors);
  fallasleep();
}

void loop() {
}
