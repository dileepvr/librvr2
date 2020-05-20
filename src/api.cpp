#include "api.h"

/* The python SDK padded this to 16 bytes...does it have to be? */
uint8_t * echo(char * sequence, int length) {
  uint8_t buffer[16]; // * buffer = (uint8_t *)malloc(sizeof(uint8_t)*16);
  uint8_t * b = buffer;
  if (length > 16) length = 16;
  for (int i=0; i<length; i++) *(b++) = *(sequence++);
  uint8_t * ret = messageSendAndRecv(ECHO_COMMAND, API_AND_SHELL_DEVICE_ID, NO_SOURCE, TARGET_ID_NORDIC, buffer, 16, 16);
  return ret;
}
