#include "rvrdefs.h"
#include "power.h"
#include "drive.h"
#include "sensor.h"

void setup() {

  init_port();

  wake();
  reset_yaw();
  reset_locator_x_and_y();

  clear_streaming_service();
  add_sensor(LOCATOR);
  configure_streaming_service();
  start_streaming_service(250);

  drive_with_heading(25, 0, 0);

  float y;
  while ((y = get_locator_Y()) < 1.5) {
    Serial.print("Distance = ");
    Serial.println(y);
  }

  drive_with_heading(0, 0, 0);

  stop_streaming_service();
  fallasleep();
}


void loop() {

}
