#include "sensor.h"
#include "power.h"

void setup() {

  /* Test for the first couple RVR commands */
  init_port();

  wake();

  clear_streaming_service();

  configure_streaming_service();  // nothing added

  add_sensor(ACCELEROMETER);
  configure_streaming_service();

  start_streaming_service(250);
  for (int i=0; i<5; i++) {
    delay(1000);
    Serial.print("Accelerometer = (");
    Serial.print(get_accelerometer_X()); Serial.print(", ");
    Serial.print(get_accelerometer_Y()); Serial.print(", ");
    Serial.print(get_accelerometer_Z()); Serial.println(")");
  }
  stop_streaming_service();

  clear_streaming_service();
  fallasleep();

}

void loop() {

}
