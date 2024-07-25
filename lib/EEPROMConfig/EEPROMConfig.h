#ifndef EEPROMCONFIG_H
#define EEPROMCONFIG_H
#include "Arduino.h"
#include "EEPROM.h"
#include <RTClib.h>
#include <time.h>
#include <SPI.h>

#define NUMBER_OF_TIMESLOTS 8
/*
07:00-08:00
08:00-08:00
08:00-07:00
23:00-01:00
23:00-00:00

// same day
if (end > start) {
    end and start are combined with the date today
}
// next day
else {
    start is combined with the date today while end is combined with the date tomorrow
}
if now > start && now < end

*/
struct timeSlot {
    unsigned short index;
    bool enabled;
    DateTime onStartTime, onEndTime; // nonvolatile time only values for on start and on end
    DateTime onStartFullTime, onEndFullTime; // volatile time with date values for on start and on end
    unsigned int durationInSeconds;
};

struct eepromConfig {
    IPAddress ipAddrSetting;
    int portSetting;
    String ssidSetting;
    String passwordSetting;

    bool ntpEnabledSetting;
    short gmtOffsetSetting;
    bool timerEnabledSetting;
    short ledSetting;
    bool relayManualSetting;
    timeSlot timeSlots[NUMBER_OF_TIMESLOTS];
};

class TimeSlot {
    public:
        // TimeSlot(timeSlot& timeslot);
        TimeSlot();
        void setTimeSlot(timeSlot& timeslot);
        int getIndex();
        void setIndex(int index);
        bool getEnabled();
        void setEnabled(bool enabled);
        DateTime getOnStartTime();
        void setOnStartTime(DateTime onStartTime);
        DateTime getOnEndTime();
        void setOnEndTime(DateTime onEndTime);
        unsigned int getDuration();
        void setDuration(unsigned int duration);
        void setOnOffFullDateTimes(DateTime now);
        bool checkIfOn(DateTime now);
    private:
        timeSlot* _tS;
};

class EEPROMConfig {
    public:
        EEPROMConfig();
        void setEEPROMConfig(eepromConfig& _eepromconfig);
        IPAddress getIPAddress();
        void setIPAddress(IPAddress ip);
        int getPort();
        void setPort(int port);
        String getSSID();
        void setSSID(String ssid);
        String getPassword();
        void setPassword(String password);

        bool getNTPEnabled();
        void setNTPEnabled(bool ntpEnabled);
        short getGMTOffset();
        void setGMTOffset(short gmtOffset);
        bool getTimerEnabled();
        void setTimerEnabled(bool timerEnabled);
        short getLEDSetting();
        void setLEDSetting(short ledSetting);
        bool getRelayManualSetting();
        void setRelayManualSetting(bool relayManualSetting);
        timeSlot& getTimeSlot(int index);
    private:
        eepromConfig _eC;
        TimeSlot* _timeslots[NUMBER_OF_TIMESLOTS];
};

#endif