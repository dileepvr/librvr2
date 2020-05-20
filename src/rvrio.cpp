#include "rvrio.h"
#include "sensor.h"
#include "drive.h"
#include "power.h"

struct message recv_msg;
bool recv_flag = false;
int data_pipe[2];
int sequence_number;
int reading;

int infrared_code;

#define TRUE 1
#define FALSE 0
#define READ  0
#define WRITE 1

void write_message(struct message * data);

void read_rover() {  // Constantly call this

  struct message *msg;
  uint8_t *sensor_data, *temperature_data;

  recv_flag = false;
  reading = 1;
  msg = read_message();

  if (msg->msghdr->deviceID == SENSOR_DEVICE_ID) {
    if (msg->msghdr->commandID == GYRO_MAX_NOTIFY) {
      set_gyro_flags(*(msg->payload));
    } else if (msg->msghdr->commandID == ROBOT_TO_ROBOT_INFRARED_MESSAGE_RECEIVED_NOTIFY) {
      infrared_code = *(msg->payload);
    } else if (msg->msghdr->commandID == COLOR_DETECTION_NOTIFY) {
      set_color_data(msg->payload);
    } else if (msg->msghdr->commandID == STREAMING_SERVICE_DATA_NOTIFY) {
      sensor_data = msg->payload;
      set_sensor_data(sensor_data);
    } else if (msg->msghdr->commandID == MOTOR_THERMAL_PROTECTION_STATUS_NOTIFY) {
      temperature_data = msg->payload;
    } else {
      recv_msg = *msg;
      recv_flag = true;
      // write_message(data_pipe[WRITE], msg);
    }
  } else if (msg->msghdr->commandID == MOTOR_STALL_NOTIFY_COMMAND) {
    set_motor_stall_notify_data(msg->payload);
  } else if (msg->msghdr->commandID == MOTOR_FAULT_NOTIFY_COMMAND) {
    set_motor_fault_state(msg->payload);
  } else if (msg->msghdr->commandID == WILL_SLEEP_NOTIFY_COMMAND) {
    set_will_sleep(msg->payload);
  } else if (msg->msghdr->commandID == DID_SLEEP_NOTIFY_COMMAND) {
    set_did_sleep(msg->payload);
  } else if (msg->msghdr->commandID == BATTERY_VOLTAGE_STATE_CHANGE_NOTIFY_COMMAND) {
    set_motor_fault_state(msg->payload);
  } else {
    recv_msg = *msg;
    recv_flag = true;
    // write_message(data_pipe[WRITE], msg);
  }
}

/***********************************************************************************/

void init_port() {

  if (!Serial) { Serial.begin(115200); }
  sequence_number = 1;
}

void close_port() {
  reading = 0;
  Serial.end();
}

uint8_t readbyte() {
    uint8_t bite;

    bite = Serial.read();
    if (bite == ESCAPE) {
        bite = Serial.read();
        bite = bite | 0x88;
    }
    return bite;
}

void writebyte(uint8_t bite) {
    uint8_t first;
    if (bite == MESSAGE_START) {
        first = ESCAPE;
        Serial.write(first);
        bite = ESC_SOP;
    } else if (bite == MESSAGE_END) {
        first = ESCAPE;
        Serial.write(first);
        bite = ESC_EOP;
    }
    Serial.write(bite);
}

struct message * read_message() {

    uint8_t bite;
    int checksum = 0;
    uint8_t buffer[256];

    struct message msgb; // * msg = (struct message*) malloc(sizeof(struct message));
    struct header headrb; // * headr = (struct header *) malloc(sizeof (struct header));
    struct message *msg;
    struct header *headr;
    msg = &msgb; headr = &headrb;
    msg->msghdr = headr;

    /* Start the message */
    bite = readbyte();
    if (bite == -1) return NULL;
    while (bite != MESSAGE_START) {
        bite = readbyte();
    }

    /* Flags */
    bite = readbyte();
    msg->msghdr->flags.allbits = bite;
    checksum += bite;

    /* Rest of the header */
    if (msg->msghdr->flags.flag_bits.has_target == 1) {
        bite = readbyte();
        msg->msghdr->targetID.wholeID = bite;;
        checksum += bite;
    }

    if (msg->msghdr->flags.flag_bits.has_source == 1) {
        bite = readbyte();
        msg->msghdr->sourceID.wholeID = bite;;
        checksum += bite;
    }

    bite = readbyte();
    msg->msghdr->deviceID = bite;
    checksum += bite;

    bite = readbyte();
    msg->msghdr->commandID = bite;
    checksum += bite;

    bite = readbyte();
    msg->msghdr->sequence_num = bite;
    checksum += bite;

    /* error code byte */
    if (msg->msghdr->flags.flag_bits.is_response) {
        bite = readbyte();
        msg->msghdr->error_code = bite;
        checksum += bite;
    }

    /* And now the payload */
    uint8_t recv_length = 0;
    bite = readbyte();
    while (bite != MESSAGE_END) {
        buffer[recv_length] = bite;
        checksum += bite;
        recv_length++;
        bite = readbyte();
    }
    recv_length--;   // account for the received checksum
    msg->loadlength = recv_length;
    uint8_t pl[recv_length]; // * pl = (uint8_t *) malloc(sizeof(uint8_t)*recv_length);
    msg->payload = pl;
    for (int i=0; i<recv_length; i++) {
        pl[i] = buffer[i];
    }
    /* Checksum */
    checksum = checksum & 0xFF ^ 0xFF;
    if (bite != checksum) {
    }

    return msg;
}

void write_message(struct message * msg) {

    uint8_t bite;
    int checksum = 0;

    /* Start the message */
    bite = MESSAGE_START;
    Serial.write(bite);

    /* Flags */
    bite = msg->msghdr->flags.allbits;
    writebyte(bite);
    checksum += bite;

    /* Rest of the header */
    if (msg->msghdr->flags.flag_bits.has_target == 1) {
        bite = msg->msghdr->targetID.wholeID;
        writebyte(bite);
        checksum += bite;
    }

    if (msg->msghdr->flags.flag_bits.has_source == 1) {
        bite = msg->msghdr->sourceID.wholeID;
        writebyte(bite);
        checksum += bite;
    }

    bite = msg->msghdr->deviceID;
    writebyte(bite);
    checksum += bite;

    bite = msg->msghdr->commandID;
    writebyte(bite);
    checksum += bite;

    bite = msg->msghdr->sequence_num;
    writebyte(bite);
    checksum += bite;

    /* And now the payload */
    if (msg->loadlength > 0) {
        uint8_t * pl = msg->payload;
        for (int i=0; i < msg->loadlength; i++) {
            bite = *pl;
            writebyte(bite);
            checksum += bite;
            pl++;
        }
    }

    /* Checksum */
    bite = checksum & 0xFF ^ 0xFF;
    writebyte(bite);

    /* Message ends */
    bite = MESSAGE_END;
    Serial.write(bite);
}

void messageSend(uint8_t cid, uint8_t did,
                 uint8_t source, uint8_t target,
                 uint8_t * payload, uint8_t payload_length) {


    /* Build the header */
    struct header headrb; // * headr = (struct header *) malloc(sizeof (struct header));
    struct header *headr;
    headr = &headrb;

    /* Flags */
    headr->flags.allbits = 0;
    headr->flags.flag_bits.is_activity = 1;
    headr->flags.flag_bits.has_target = (target > 0 ? 1 : 0);
    headr->flags.flag_bits.has_source = (source > 0 ? 1 : 0);

    /* Rest of the header */
    headr->targetID.wholeID = target;
    headr->sourceID.wholeID = source;
    headr->deviceID = did;
    headr->commandID = cid;
    headr->sequence_num = sequence_number++;

    /* Build the message */
    struct message msgb; // * msg = (struct message*) malloc(sizeof(struct message));
    struct message *msg;
    msg = &msgb;

    msg->msghdr = headr;
    msg->payload = payload;
    msg->loadlength = payload_length;

    /* Write it! */
    write_message(msg);
}

uint8_t * messageSendAndRecv(uint8_t cid, uint8_t did,
                              uint8_t source, uint8_t target,
                              uint8_t * payload, uint8_t payload_length, uint8_t recv_length) {


     /* Build the header */
    struct header headrb; // * headr = (struct header *) malloc(sizeof (struct header));
    struct header *headr;
    headr = &headrb;

    /* Flags */
    headr->flags.allbits = 0;
    headr->flags.flag_bits.is_activity = 1;
    headr->flags.flag_bits.response_requested = 1;
    headr->flags.flag_bits.has_target = (target > 0 ? 1 : 0);
    headr->flags.flag_bits.has_source = (source > 0 ? 1 : 0);

    /* Rest of the header */
    headr->targetID.wholeID = target;
    headr->sourceID.wholeID = source;
    headr->deviceID = did;
    headr->commandID = cid;
    headr->sequence_num = sequence_number++;

    /* Build the message */
    struct message msgb; // * msg = (struct message*) malloc(sizeof(struct message));
    struct message *msg;
    msg = &msgb;

    msg->msghdr = headr;
    msg->payload = payload;
    msg->loadlength = payload_length;

    /* Write it! */
    write_message(msg);

    /* and read it! */
    struct message * response;
    response = read_message();

    return response->payload;
}

uint8_t * messageRecv() {

    struct message * response;
    read_rover();
    if(recv_flag) {
      response = &recv_msg;
      recv_flag = false;
    }
    //struct message * response = read_message(serial_port_fd);
    return response->payload;
}
