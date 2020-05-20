#include "rvrdefs.h"
#include "power.h"
#include "drive.h"

void setup() {
    init_port();

    wake();
    reset_yaw();

    drive_raw_motors(RAW_MOTOR_MODE_FORWARD, 128, RAW_MOTOR_MODE_FORWARD, 128);

    delay(2000);

    drive_raw_motors(RAW_MOTOR_MODE_FORWARD, 0, RAW_MOTOR_MODE_FORWARD, 0);
    fallasleep();
}

void loop() {
}
