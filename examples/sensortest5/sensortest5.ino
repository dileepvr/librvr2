#include "sensor.h"
#include "power.h"
#include "drive.h"

void setup() {

  /* Test for the first couple RVR commands */
  init_port();

  wake();
  delay(2000);

  printf("*** Sensing while driving ***\n");

  reset_yaw();
  reset_locator_x_and_y();
  add_sensor(LOCATOR);
  add_sensor(VELOCITY);
  add_sensor(SPEED);

  configure_streaming_service();
  start_streaming_service(250);
  delay(1000);
  Serial.print("Locator = ("); Serial.print(get_locator_X());
  Serial.print(", "); Serial.print(get_locator_Y());
  Serial.println(")");
  Serial.print("Velocity = ("); Serial.print(get_velocity_X());
  Serial.print(", "); Serial.print(get_velocity_Y());
  Serial.println(")");
  Serial.print("Speed = ");
  Serial.println(get_speed());
  Serial.print("---------------------------------------\n");

  drive_with_heading(30, 0, 0);

  for (int i=0; i<3; i++) {
    delay(1000);
    Serial.print("Locator = ("); Serial.print(get_locator_X());
    Serial.print(", "); Serial.print(get_locator_Y());
    Serial.println(")");
    Serial.print("Velocity = ("); Serial.print(get_velocity_X());
    Serial.print(", "); Serial.print(get_velocity_Y());
    Serial.println(")");
    Serial.print("Speed = "); Serial.println(get_speed());
    Serial.print("---------------------------------------\n");
  }

  drive_with_heading(30, 180, 0);
  for (int i=0; i<3; i++) {
    delay(1000);
    Serial.print("Locator = ("); Serial.print(get_locator_X());
    Serial.print(", "); Serial.print(get_locator_Y());
    Serial.println(")");
    Serial.print("Velocity = ("); Serial.print(get_velocity_X());
    Serial.print(", "); Serial.print(get_velocity_Y());
    Serial.println(")");
    Serial.print("Speed = "); Serial.println(get_speed());
    Serial.print("---------------------------------------\n");
  }

  drive_with_heading(0,0,0);

  stop_streaming_service();
  clear_streaming_service();
  fallasleep();
}

void loop() {
}
