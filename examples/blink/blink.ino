#include "io.h"
#include "power.h"

void setup() {
    byte off[32];
    byte red[32];
    byte green[32];

    init_port();
    // Serial.begin(115200);

    wake();
    delay(2000);

    for (int i=0; i<32; i++) {
        off[i] = 0x00;
        red[i] = 0x00;
        green[i] = 0x00;
    }
    set_all_leds(ALL_LIGHTS, off);
    delay(1000);
    for (int i=0; i<32; i+=3) red[i] = 0xFF;
    for (int i=1; i<32; i+=3) green[i] = 0xFF;

    for (int i=0; i<10; i++) {
        set_all_leds(LEFT_BRAKELIGHT, red);
        delay(1000);
        set_all_leds(RIGHT_BRAKELIGHT, green);
        delay(1000);
        set_all_leds(LEFT_BRAKELIGHT, off);
        delay(1000);
        set_all_leds(RIGHT_BRAKELIGHT, off);
        delay(1000);
    }

}

void loop() {
}
