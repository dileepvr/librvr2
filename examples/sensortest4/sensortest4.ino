#include "sensor.h"
#include "power.h"
#include "drive.h"

void setup() {

  /* Test for the first couple RVR commands */
  init_port();
  int flag = 0;

  wake();
  delay(2000);

  Serial.print("*** One sensor at a time ***\n");

  for (int sensor=0; sensor < 8; sensor++) {
    flag = (flag == 0 ? DRIVE_FLAG_DRIVE_REVERSE : 0);
    drive_with_heading(30,0,flag);
    clear_streaming_service();
    delay(1000);
    reset_sensor_list();
    switch (sensor) {
    case 0:
      add_sensor(QUATERNION);
      break;
    case 1:
      add_sensor(ACCELEROMETER);
      break;
    case 2:
      add_sensor(IMU);
      break;
    case 3:
      add_sensor(GYROSCOPE);
      break;
    case 4:
      reset_locator_x_and_y();
      add_sensor(LOCATOR);
      break;
    case 5:
      add_sensor(VELOCITY);
      break;
    case 6:
      add_sensor(SPEED);
      break;
    case 7:
      add_sensor(AMBIENT_LIGHT);
      break;
    }

    configure_streaming_service();
    start_streaming_service(250);

    for (int i=0; i<3; i++) {
      delay(1000);
      switch (sensor) {
      case 0:
        Serial.print("Quaternion = (");
        Serial.print(get_quaternion_W()); Serial.print(", ");
        Serial.print(get_quaternion_X()); Serial.print(", ");
        Serial.print(get_quaternion_Y()); Serial.print(", ");
        Serial.print(get_quaternion_Z()); Serial.println(")");
        break;
      case 1:
        Serial.print("Accelerometer = (");
        Serial.print(get_accelerometer_X()); Serial.print(", ");
        Serial.print(get_accelerometer_Y()); Serial.print(", ");
        Serial.print(get_accelerometer_Z()); Serial.println(")");
        break;
      case 2:
        Serial.print("Roll: "); Serial.print(get_roll());
        Serial.print(", Pitch: "); Serial.print(get_pitch());
        Serial.print(", Yaw: "); Serial.println(get_yaw());
        break;
      case 3:
        Serial.print("Gyroscope = ("); Serial.print(get_gyroscope_X());
        Serial.print(", "); Serial.print(get_gyroscope_Y());
        Serial.print(", "); Serial.print(get_accelerometer_Z());
        Serial.println(")");
        break;
      case 4:
        Serial.print("Locator = ("); Serial.print(get_locator_X());
        Serial.print(", "); Serial.print(get_locator_Y());
        Serial.println(")");
        break;
      case 5:
        Serial.print("Velocity = ("); Serial.print(get_velocity_X());
        Serial.print(", "); Serial.print(get_velocity_Y());
        Serial.println(")");
        break;
      case 6:
        Serial.print("Speed = "); Serial.println(get_speed());
        break;
      case 7:
        Serial.print("Light = "); Serial.println(get_light());
        break;
      }
    }
    stop_streaming_service();
    delay(1000);
  }
  drive_with_heading(0,0,0);
  clear_streaming_service();
  fallasleep();

}

void loop() {
}
