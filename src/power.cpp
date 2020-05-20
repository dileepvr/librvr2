#include "power.h"

void wake() {
  messageSend(WAKE_COMMAND, POWER_DEVICE_ID, NO_SOURCE, TARGET_ID_NORDIC, NULL, 0);
}

void fallasleep() {
  messageSend(SLEEP_COMMAND, POWER_DEVICE_ID, NO_SOURCE, TARGET_ID_NORDIC, NULL, 0);
}

uint8_t get_battery_percentage() {
  uint8_t * percentage = messageSendAndRecv(GET_BATTERY_PERCENTAGE_COMMAND, POWER_DEVICE_ID, NO_SOURCE, TARGET_ID_NORDIC, NULL, 0, 1);
  return percentage[0];
}

uint8_t get_battery_voltage_state() {
  uint8_t * state = messageSendAndRecv(GET_BATTERY_VOLTAGE_STATE_COMMAND, POWER_DEVICE_ID, NO_SOURCE, TARGET_ID_NORDIC, NULL, 0, 1);
  return *state;
}

float get_battery_voltage_in_volts(uint8_t reading_type) {
  union {
    uint32_t intvalue;
    float floatvalue;
  } cvfloat;
  uint8_t * type_buffer = (uint8_t *) malloc(sizeof(uint8_t));
  type_buffer[0] = reading_type;
  uint8_t * voltage =
    messageSendAndRecv(GET_BATTERY_VOLTAGE_IN_VOLTS_COMMAND, POWER_DEVICE_ID,
                       NO_SOURCE, TARGET_ID_NORDIC,
                       type_buffer, 1, 4);
  uint32_t integer = voltage[0] << 24 | voltage[1] << 16 | voltage[2] << 8 | voltage[3];
  cvfloat.intvalue = integer;

  return cvfloat.floatvalue;
}

float *get_battery_voltage_state_thresholds() {
  union {
    uint32_t intvalue;
    float floatvalue;
  } cvfloat;
  float * thresh_buffer = (float *) malloc(sizeof(float)*3);
  uint8_t * data =
    messageSendAndRecv(GET_BATTERY_VOLTAGE_STATE_THRESHOLDS_COMMAND, POWER_DEVICE_ID,
                       NO_SOURCE, TARGET_ID_NORDIC,
                       NULL, 0, 12);

  uint32_t integer = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
  cvfloat.intvalue = integer;
  thresh_buffer[0] = cvfloat.floatvalue;
  integer = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
  cvfloat.intvalue = integer;
  thresh_buffer[1] = cvfloat.floatvalue;
  integer = data[8] << 24 | data[9] << 16 | data[10] << 8 | data[11];
  cvfloat.intvalue = integer;
  thresh_buffer[3] = cvfloat.floatvalue;

  return thresh_buffer;
}

float get_current_sense_amplifier_current(uint8_t amplifier_id) {
  union {
    uint32_t intvalue;
    float floatvalue;
  } cvfloat;
  uint8_t * amp_buffer = (uint8_t *) malloc(sizeof(uint8_t));
  amp_buffer[0] = amplifier_id;
  uint8_t * amps =
    messageSendAndRecv(GET_CURRENT_SENSE_AMPLIFIER_CURRENT_COMMAND, POWER_DEVICE_ID,
                       NO_SOURCE, TARGET_ID_NORDIC,
                       amp_buffer, 1, 4);
  uint32_t integer = amps[0] << 24 | amps[1] << 16 | amps[2] << 8 | amps[3];
  cvfloat.intvalue = integer;

  return cvfloat.floatvalue;
}

int will_sleep, did_sleep;

void set_will_sleep(uint8_t *data) {
  will_sleep = data[0];
}

int get_will_sleep() { return will_sleep; }

void set_did_sleep(uint8_t *data) {
  did_sleep = data[0];
}

int get_did_sleep() {return did_sleep; }

int battery_voltage_state_changed;

void set_battery_voltage_state_change(uint8_t *data) {
  battery_voltage_state_changed = data[0];
}

int get_battery_voltage_state_changed() { return battery_voltage_state_changed; }
