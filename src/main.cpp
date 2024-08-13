#include <Arduino.h>
#include "EEPROMConfig.h"

EEPROMConfig eC(0);

void setup() {
  delay(10000);
  Serial.begin(115200);
  eC.begin();
  DateTime now = DateTime(2024, 7,26, 7,0,0);
  eC.load(now);
  Serial.println("Testing the EEPROM Configuration load and save");
  Serial.println("Loaded froM EEPROM");
  eC.print();
  Serial.println();
  Serial.println("Modifying the EEPROM configuration");
  eC.setIPAddress(IPAddress(192,168,5,60));
  eC.setPort(5555);
  eC.setSSID("wifi-ssid");
  eC.setPassword("wifi-password");
  eC.setName("basil_ESP32");
  eC.setNTPEnabled(true);
  eC.setTimerEnabled(true);
  eC.setGMTOffset(8);
  eC.setLEDSetting(2);
  eC.setRelayManualSetting(false);

  // now = DateTime(2024, 7,26, 7,0,0);
  // TimeSlot& tS0 = eC.getTimeSlot(0); 
  // tS0.setEnabled(true);
  // tS0.setOnStartTime(8,0,0);
  // tS0.setOnEndTime(10,0,0, now);

  TimeSlot* tSs[10];
  tSs[0] = eC.getTimeSlot(0);
  tSs[0]->setEnabled(true);
  tSs[0]->setOnStartTime(8,0,0, now);
  tSs[0]->setOnEndTime(10,0,0, now);

  tSs[1] = eC.getTimeSlot(1); 
  tSs[1]->setEnabled(true);
  tSs[1]->setOnStartTime(8,0,0, now);
  tSs[1]->setOnEndTime(8,0,0, now);

  tSs[2] = eC.getTimeSlot(2); 
  tSs[2]->setEnabled(true);
  tSs[2]->setOnStartTime(8,0,0, now);
  tSs[2]->setOnEndTime(7,0,0, now);

  tSs[3] = eC.getTimeSlot(3); 
  tSs[3]->setEnabled(true);
  tSs[3]->setOnStartTime(8,0,0, now);
  tSs[3]->setDuration(60*60*3, now);

  tSs[4] = eC.getTimeSlot(4); 
  tSs[4]->setEnabled(true);
  tSs[4]->setOnStartTime(8,0,0, now);
  tSs[4]->setDuration(60*60*15, now);

  Serial.println();
  Serial.println("Printing the EEPROM configuration before saving it to the EEPROM");
  eC.print();
  eC.save();

  // simulate different times of the day and see if the automatic timer works 
  // first set the TimeSlots
  // timeslot 0 is from 08:00-10:00
  tSs[0] = eC.getTimeSlot(0);
  tSs[0]->setEnabled(true);
  tSs[0]->setOnStartTime(8,0,0, now);
  tSs[0]->setOnEndTime(10,0,0, now);

  // timeslot 1 is from 12:00-15:00
  tSs[1] = eC.getTimeSlot(1);
  tSs[1]->setEnabled(true);
  tSs[1]->setOnStartTime(12,0,0, now);
  tSs[1]->setOnEndTime(15,0,0, now);

  // timeslot 2 is from 10:30 to 11:30 but is disabled
  tSs[2] = eC.getTimeSlot(2);
  tSs[2]->setEnabled(false);
  tSs[2]->setOnStartTime(10,30,0, now);
  tSs[2]->setOnEndTime(11,30,0, now);

  // timeslot 3 is from 22:00 to 02:00 the next day
  tSs[3] = eC.getTimeSlot(3);
  tSs[3]->setEnabled(true);
  tSs[3]->setOnStartTime(22,0,0, now);
  tSs[3]->setOnEndTime(02,0,0, now);

  // disable timeslots 4-end
  for (int i=4;i<NUMBER_OF_TIMESLOTS;i++) {
    tSs[i] = eC.getTimeSlot(i);
    tSs[i]->setEnabled(false);
  }

  Serial.println();
  eC.save();
  Serial.println("Testing of checkIfAnyTimeSlotOn()");
  eC.print();
  Serial.println();

  // testing getISOTime for each timeslot 
  for (int i=0;i<NUMBER_OF_TIMESLOTS;i++) {
    Serial.printf("Timeslot %d\n", i);
    Serial.printf("start time ISO string = %s\n", eC.getTimeSlot(i)->getOnStartTimeISOString());
    Serial.printf("end time ISO string = %s\n", eC.getTimeSlot(i)->getOnEndTimeISOString());
  }

  // testing setISOTime in a timeslot 
  eC.getTimeSlot(6)->setOnStartTimeISOString("05:00:00Z", now);
  eC.getTimeSlot(6)->setOnEndTimeISOString("10:00:00Z", now);
  eC.getTimeSlot(6)->print();

  // if the time is 06:00, relay must be off.
  now = DateTime(2024, 7, 26, 6, 0, 0);
  Serial.printf("06:00 is %d, it must be 0.\n\n", eC.checkIfAnyTimeSlotOn(now));

  // if the time is 09:00, relay must be on.
  now = DateTime(2024, 7, 26, 9, 0, 0);
  Serial.printf("09:00 is %d, it must be 1.\n\n", eC.checkIfAnyTimeSlotOn(now));

  // if the time is 11:00, relay must be off.
  now = DateTime(2024, 7, 26, 11, 0, 0);
  Serial.printf("11:00 is %d, it must be 0.\n\n", eC.checkIfAnyTimeSlotOn(now));

  // if the time is 12:00, relay must be on.
  now = DateTime(2024, 7, 26, 12, 0, 1);
  Serial.printf("12:00 is %d, it must be 1.\n\n", eC.checkIfAnyTimeSlotOn(now));

  // if the time is 14:00, relay must be on.
  now = DateTime(2024, 7, 26, 14, 0, 0);
  Serial.printf("14:00 is %d, it must be 1.\n\n", eC.checkIfAnyTimeSlotOn(now));

  // if the time is 16:00, relay must be off.
  now = DateTime(2024, 7, 26, 16, 0, 0);
  Serial.printf("16:00 is %d, it must be 0.\n\n", eC.checkIfAnyTimeSlotOn(now));
  
  // if the time is 23:00, relay must be on.
  now = DateTime(2024, 7, 26, 23, 0, 0);
  Serial.printf("23:00 is %d, it must be 1.\n\n", eC.checkIfAnyTimeSlotOn(now));

  // if the time is 00:00 the next day, relay must be on.
  now = DateTime(2024, 7, 27, 0, 0, 0);
  Serial.printf("00:00 the next day is %d, it must be 1.\n\n", eC.checkIfAnyTimeSlotOn(now));
}

void loop() {
  // put your main code here, to run repeatedly:
}
