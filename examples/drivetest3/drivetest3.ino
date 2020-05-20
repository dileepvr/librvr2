#include "rvrdefs.h"
#include "power.h"
#include "drive.h"
#include "sensor.h"

void setup() {

  char c;

  init_port();

  Serial.print("*** Test driving with heading ***\n");

  wake();
  reset_yaw();

  Serial.print("*** Forward for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, 0);
  delay(2000);
  drive_with_heading(0, 0, 0);

  Serial.print("*** Reverse for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, DRIVE_FLAG_DRIVE_REVERSE);
  delay(2000);
  drive_with_heading(0, 0, 0);

  Serial.print("*** Heading in left direction for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, DRIVE_FLAG_LEFT_DIRECTION);
  delay(2000);
  drive_with_heading(0, 0, 0);

  Serial.print("*** Forward for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, 0);
  delay(2000);
  drive_with_heading(0, 0, 0);

  Serial.print("*** Heading in right direction for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, DRIVE_FLAG_RIGHT_DIRECTION);
  delay(2000);
  drive_with_heading(0, 0, 0);

  Serial.print("*** Forward for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, 0);
  delay(2000);
  drive_with_heading(0, 0, 0);

  Serial.print("*** Driving backwards for 2 seconds ***\n");
  Serial.print("*** Enter any value to start");
  while(!Serial.available()) { } // Wait for user input
  c = Serial.read();
  drive_with_heading(50, 0, DRIVE_FLAG_DRIVE_REVERSE);
  delay(2000);
  drive_with_heading(0, 0, 0);

  fallasleep();
}

void loop() {


}
