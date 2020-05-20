#include "connection.h"

uint8_t * get_bluetooth_advertising_name() {
  uint8_t * btname =
    messageSendAndRecv(GET_BLUETOOTH_ADVERT, CONNECTION_DEVICE_ID,
                       NO_SOURCE, TARGET_ID_NORDIC,
                       NULL, 0, 0);
  return btname;
}
