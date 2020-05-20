#include "drive.h"

void drive_raw_motors(uint8_t left_mode, uint8_t left_speed, uint8_t right_mode, uint8_t right_speed) {
  uint8_t payload[4]; // *payload = (uint8_t *)malloc(sizeof(uint8_t) * 4);
  payload[0] = left_mode;
  payload[1] = left_speed;
  payload[2] = right_mode;
  payload[3] = right_speed;

  messageSend(RAW_MOTOR_COMMAND, DRIVE_DEVICE_ID,
              NO_SOURCE, TARGET_ID_ST,
              payload, 4);
}

void reset_yaw() {
  messageSend(RESET_YAW_COMMAND, DRIVE_DEVICE_ID,
              NO_SOURCE, TARGET_ID_ST,
              NULL, 0);
}

void drive_with_heading(byte speed, int heading, byte flags) {
  uint8_t payload[4]; // *payload = (uint8_t *)malloc(sizeof(uint8_t) * 4);
  payload[0] = speed;
  payload[1] = heading >> 8 & 0xFF;
  payload[2] = heading  & 0xFF;
  payload[3] = flags;

  messageSend(DRIVE_WITH_HEADING_COMMAND, DRIVE_DEVICE_ID,
              NO_SOURCE, TARGET_ID_ST,
              payload, 4);
}

void enable_motor_stall_notify(int isEnabled) {
  uint8_t *payload; // = (uint8_t *)malloc(sizeof(uint8_t));
  payload[0] = isEnabled & 0xFF;

  messageSend(ENABLE_MOTOR_STALL_NOTIFY_COMMAND, DRIVE_DEVICE_ID,
              NO_SOURCE, TARGET_ID_ST,
              payload, 1);
}

void enable_motor_fault_notify(int isEnabled) {
  uint8_t *payload; // = (uint8_t *)malloc(sizeof(uint8_t));
    payload[0] = isEnabled & 0xFF;

    messageSend(ENABLE_MOTOR_FAULT_NOTIFY_COMMAND, DRIVE_DEVICE_ID,
                NO_SOURCE, TARGET_ID_ST,
                payload, 1);
}

int get_motor_fault_state() {
    uint8_t * state =
        messageSendAndRecv(GET_MOTOR_FAULT_STATE_COMMAND, DRIVE_DEVICE_ID,
                           NO_SOURCE, TARGET_ID_ST,
                           NULL, 0, 1);
    return state[0];
}

//---------------------------------------------------------------------------------------------------
//
//  Notify calls

uint8_t motor_index;
int is_triggered, motor_fault_state;

void set_motor_stall_notify_data(uint8_t *data) {
    motor_index = data[0];
    is_triggered = data[1];
}

uint8_t get_motor_index() { return motor_index; }
int get_is_triggered() { return is_triggered; }

void set_motor_fault_state(uint8_t *data) {
    motor_fault_state = data[0];
}
