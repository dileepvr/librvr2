#include <Arduino.h>
#include <HardwareSerial.h>

#include "rvrdefs.h"
#include "notify.h"

#define ESCAPE   0xab
#define ESC_ESC  0x23
#define ESC_SOP  0x05
#define ESC_EOP  0x50

void init_port();
void close_port();
void set_logging_level(int level);

struct message * read_message();
int data_waiting();
void messageSend(uint8_t cid, uint8_t did,
                 uint8_t source, uint8_t target,
                 uint8_t * payload, uint8_t payload_length);
uint8_t * messageSendAndRecv(uint8_t cid, uint8_t did,
                              uint8_t source, uint8_t target,
                              uint8_t * payload, uint8_t payload_length, uint8_t recv_length);
uint8_t * messageRecv();
char * errmsg(int error_code);
