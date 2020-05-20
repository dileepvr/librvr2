#include "rvrio.h"
#include "power.h"
#include "system.h"

void setup() {

  /* Test for the first couple RVR commands */
  init_port();

  wake();

  uint16_t * application_version = get_main_application_version();
  Serial.print("*** Application version: ");
  Serial.print(application_version[0]); Serial.print(".");
  Serial.print(application_version[1]); Serial.print(".");
  Serial.println(application_version[2]);

  uint16_t * bootloader = get_bootloader_version();
  Serial.print("*** Bootloader version: ");
  Serial.print(bootloader[0]); Serial.print(".");
  Serial.print(bootloader[1]); Serial.print(".");
  Serial.println(bootloader[2]);

  uint8_t * macaddress = get_mac_address();
  Serial.print("*** MAC address is ");
  Serial.println((char*)macaddress);

  uint8_t revision = get_board_revision();
  Serial.print("*** Board revision is ");
  Serial.println(revision);

  uint16_t statsid = get_stats_id();
  Serial.print("*** Stats ID is ");
  Serial.println(statsid);

  uint8_t * procname = get_processor_name();
  Serial.print("*** Processor name ");
  Serial.println((char*)procname);

  uint8_t * sku = get_sku();
  Serial.print("*** SKU is ");
  Serial.println((char*)sku);

  long millis = get_core_up_time_in_milliseconds();
  float minutes = millis / 1000.0 / 60.0;
  Serial.print("*** Uptime = ");
  Serial.print(minutes); Serial.println(" minutes.");
  fallasleep();
}

void loop() {
}
