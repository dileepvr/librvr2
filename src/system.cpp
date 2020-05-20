#include <stdio.h>
#include <stdlib.h>
#include "system.h"

uint16_t * get_main_application_version() {
  uint16_t version[3]; // * version = (uint16_t *)malloc(sizeof(uint16_t)*3);

    uint8_t * response =
        messageSendAndRecv(GET_MAIN_APPLICATION_VERSION_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 6);

    version[0] = response[0]*256+response[1];
    version[1] = response[2]*256+response[3];
    version[2] = response[4]*256+response[5];

    return version;

}

uint16_t * get_bootloader_version() {
  uint16_t version[3]; // * version = (uint16_t *)malloc(sizeof(uint16_t)*3);

    uint8_t * response =
        messageSendAndRecv(GET_BOOTLOADER_VERSION_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 6);

    version[0] = response[0]*256+response[1];
    version[1] = response[2]*256+response[3];
    version[2] = response[4]*256+response[5];

    return version;
}

uint8_t * get_mac_address() {
    uint8_t * response;
    uint8_t address[13]; // * address = (char *)malloc(sizeof(char)*13);

    response = messageSendAndRecv(GET_MAC_ADDRESS_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 12);
    for (int i=0; i<12; i++) address[i] = response[i];
    address[13] = 0;
    return address;
}

uint8_t get_board_revision() {
    uint8_t * response =
        messageSendAndRecv(GET_BOARD_REVISION_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 1);
    return response[0];

}

uint16_t get_stats_id() {
    uint16_t stats_id;

    uint8_t * response =
        messageSendAndRecv(GET_STATS_ID_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 2);
    stats_id = response[0]*256+response[1];
    return stats_id;
}

uint8_t * get_processor_name() {
    uint8_t * response;

    response = messageSendAndRecv(GET_PROCESSOR_NAME_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 0);
    return response;
}

uint8_t * get_sku() {
    uint8_t * response;

    response = messageSendAndRecv(GET_SKU_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 0);

    return response;
}

uint64_t get_core_up_time_in_milliseconds() {
    uint8_t * response;

    response = messageSendAndRecv(GET_CORE_UP_TIME_IN_MILLISECONDS_COMMAND, SYSTEM_INFO_DEVICE_ID,
                                  NO_SOURCE, TARGET_ID_NORDIC,
                                  NULL, 0, 8);

    return response[0]*256*256*256*256*256*256*256 +
              response[1]*256*256*256*256*256*256 +
              response[2]*256*256*256*256*256* +
              response[3]*256*256*256*256 +
              response[4]*256*256*256 +
              response[5]*256*256 + response[6]*256 + response[7];
}
