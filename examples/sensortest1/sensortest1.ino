#include "sensor.h"
#include "power.h"

void setup() {

  init_port();

  wake();
  delay(2000);

}

void loop() {

  float ambient_level;

  ambient_level = get_ambient_light_sensor_value();
  Serial.print("Ambient light level = ");
  Serial.println(ambient_level);

}
