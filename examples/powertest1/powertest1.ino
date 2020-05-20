#include "power.h"

void setup() {

  /* Test for the first couple RVR commands */
  init_port();

  wake();

  int batts = get_battery_percentage();
  Serial.print("Battery age reported as ");
  Serial.println(batts);

  int state = get_battery_voltage_state();
  Serial.print("Battery state is ");
  Serial.println(state);
  fallasleep();
}

void loop() {
}
