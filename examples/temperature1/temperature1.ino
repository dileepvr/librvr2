#include "sensor.h"
#include "power.h"
#include "drive.h"

void setup() {
  float temperatureL, temperatureR;
  char buffer[256];
  init_port();

  wake();
  delay(2000);

  get_motor_thermal_protection_status();
  temperatureL = get_left_motor_temperature();
  temperatureR = get_right_motor_temperature();
  sprintf(buffer, "Left motor temp = %f\nRight motor temp = %f\n",
        temperatureL, temperatureR);
  Serial.print(buffer);

  drive_raw_motors(RAW_MOTOR_MODE_FORWARD, 128, RAW_MOTOR_MODE_FORWARD, 128);
  delay(5000);
  drive_raw_motors(RAW_MOTOR_MODE_FORWARD, 0, RAW_MOTOR_MODE_FORWARD, 0);

  get_motor_thermal_protection_status();
  temperatureL = get_left_motor_temperature();
  temperatureR = get_right_motor_temperature();
  sprintf(buffer, "Left motor temp = %f\nRight motor temp = %f\n",
          temperatureL, temperatureR);
  Serial.print(buffer);
  fallasleep();

}

void loop() {
}
