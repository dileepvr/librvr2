#include "power.h"

void setup() {

  /* Test for the first couple RVR commands */
  init_port();

  wake();

  float volts = get_battery_voltage_in_volts(0);
  Serial.print("Voltage reading -- calibrated and filtered -- is ");
  Serial.println(volts);
  volts = get_battery_voltage_in_volts(1);
  Serial.print("Voltage reading -- calibrated and unfiltered -- is ");
  Serial.println(volts);
  volts = get_battery_voltage_in_volts(2);
  Serial.print("Voltage reading -- uncalibrated and unfiltered -- is ");
  Serial.println(volts);
  fallasleep();

}

void loop() {
}
