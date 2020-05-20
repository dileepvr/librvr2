#include "rvrdefs.h"
#include "power.h"
#include "drive.h"
#include "sensor.h"

void setup() {
  char buf[256];
  init_port();

  Serial.print("*** Test driving with heading ***\n");

  wake();
  reset_yaw();
  reset_locator_x_and_y();

  add_sensor(LOCATOR);
  configure_streaming_service();
  start_streaming_service(250);

  drive_with_heading(50, 0, 0);
  delay(1000);
  sprintf(buf, "(%f, %f)\n", get_locator_X(), get_locator_Y());
  Serial.print(buf);

  drive_with_heading(50, 0, DRIVE_FLAG_DRIVE_REVERSE);
  delay(1000);
  sprintf(buf, "(%f, %f)\n", get_locator_X(), get_locator_Y());
  Serial.print(buf);

  drive_with_heading(50, 90, 0);
  delay(1000);
  sprintf(buf, "(%f, %f)\n", get_locator_X(), get_locator_Y());
  Serial.print(buf);

  drive_with_heading(50, 270, 0);
  delay(1000);
  sprintf(buf, "(%f, %f)\n", get_locator_X(), get_locator_Y());
  Serial.print(buf);

  drive_with_heading(0, 0, 0);
  sprintf(buf, "(%f, %f)\n", get_locator_X(), get_locator_Y());
  Serial.print(buf);


  stop_streaming_service();
  clear_streaming_service();
  fallasleep();
}

void loop() {
}
