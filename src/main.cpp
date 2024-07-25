#include <Arduino.h>
#include "EEPROMConfig.h"

EEPROMConfig eC(0);

void setup() {
  Serial.begin(115200);
  eC.begin();
  eC.load();
  eC.print();

  eC.setIPAddress(IPAddress(192,168,5,60));
  eC.setPort(5555);
  eC.setSSID("wifi-ssid");
  eC.setPassword("wifi-password");
  eC.setNTPEnabled(true);
  eC.setTimerEnabled(true);
  eC.setGMTOffset(8);
  eC.setLEDSetting(2);
  eC.setRelayManualSetting(false);

  DateTime now = DateTime(2024, 7,26, 7,0,0);
  // TimeSlot& tS0 = eC.getTimeSlot(0); 
  // tS0.setEnabled(true);
  // tS0.setOnStartTime(8,0,0);
  // tS0.setOnEndTime(10,0,0, now);

  TimeSlot* tSs[10];
  tSs[0] = eC.getTimeSlot(0);
  tSs[0]->setEnabled(true);
  tSs[0]->setOnStartTime(8,0,0);
  tSs[0]->setOnEndTime(10,0,0, now);

  tSs[1] = eC.getTimeSlot(1); 
  tSs[1]->setEnabled(true);
  tSs[1]->setOnStartTime(8,0,0);
  tSs[1]->setOnEndTime(8,0,0, now);

  tSs[2] = eC.getTimeSlot(2); 
  tSs[2]->setEnabled(true);
  tSs[2]->setOnStartTime(8,0,0);
  tSs[2]->setOnEndTime(7,0,0, now);

  tSs[3] = eC.getTimeSlot(3); 
  tSs[3]->setEnabled(true);
  tSs[3]->setOnStartTime(8,0,0);
  tSs[3]->setDuration(60*60*3, now);

  tSs[4] = eC.getTimeSlot(4); 
  tSs[4]->setEnabled(true);
  tSs[4]->setOnStartTime(8,0,0);
  tSs[4]->setDuration(60*60*15, now);

  eC.print();
  eC.save();
}

void loop() {
  // put your main code here, to run repeatedly:
}
