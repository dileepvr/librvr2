
#include "power.h"
#include "io.h"

#define TRUE 1

#define RED    187, 24, 0
#define GREEN  0, 91, 72
#define BLUE   0, 79, 154
#define PURPLE 0, 0, 28
#define YELLOW 251, 227, 5
#define WHITE  250, 245, 255

void swirl(int color) {
  uint32_t leds = 0;
  byte colors[32];

  for (int led=0; led < 32; led += 3) {
    for (int i=0; i<32; i++) colors[i] = 0x00;
    set_all_leds(ALL_LIGHTS, colors);

    leds = 0;
    leds = 1 << led | 1 << (led+1) | led << (led+2);

    colors[0] = color >> 16 & 0xFF;
    colors[1] = color >> 8 & 0xFF;
    colors[2] = color & 0xFF;

    set_all_leds(leds, colors);
    delay(1000);
  }
}

void setup() {

  /* Test for the first couple RVR commands */
  init_port();

  wake();
  delay(2000);

  swirl(0xFF0000);
  delay(1000);
  swirl(0x00FF00);
  delay(1000);
  swirl(0x0000FF);
  fallasleep();

}

void loop() {
}
