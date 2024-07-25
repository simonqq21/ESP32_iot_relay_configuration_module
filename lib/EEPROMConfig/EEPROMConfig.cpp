#include "EEPROMConfig.h"

/*
TimeSlot class methods
*/
// TimeSlot::TimeSlot(timeSlot& timeslot): _tS(timeslot) {
// }

TimeSlot::TimeSlot() {
    timeSlot* _tS = (timeSlot*)malloc(sizeof(timeSlot));
}

void TimeSlot::setTimeSlot(timeSlot& timeslot) {
    _tS = &timeslot;
}

int TimeSlot::getIndex() {
    return _tS->index;
}

void TimeSlot::setIndex(int index) {
    _tS->index=index;
}

bool TimeSlot::getEnabled() {
    return _tS->enabled;
}

void TimeSlot::setEnabled(bool enabled) {
    _tS->enabled=enabled;
}

DateTime TimeSlot::getOnStartTime() {
    return _tS->onStartTime;
}

void TimeSlot::setOnStartTime(DateTime onStartTime) {
    _tS->onStartTime=onStartTime;
}

DateTime TimeSlot::getOnEndTime() {
    return _tS->onEndTime;
}

void TimeSlot::setOnEndTime(DateTime onEndTime) {
    _tS->onEndTime=onEndTime;
}

unsigned int TimeSlot::getDuration() {
    return _tS->durationInSeconds;
}

void TimeSlot::setDuration(unsigned int duration) {
    _tS->durationInSeconds=duration;
}

void TimeSlot::setOnOffFullDateTimes(DateTime now) {

}

bool TimeSlot::checkIfOn(DateTime now) {
    return false;
}



/*
EEPROMConfig class methods
*/
EEPROMConfig::EEPROMConfig() {
    eepromConfig* _eC = (eepromConfig*)malloc(sizeof(eepromConfig));
    TimeSlot* _timeslots = (TimeSlot*)malloc(sizeof(TimeSlot)*NUMBER_OF_TIMESLOTS);
}

void EEPROMConfig::setEEPROMConfig(eepromConfig& _eepromconfig) {
    _eC = _eepromconfig;
    for (int i=0;i<NUMBER_OF_TIMESLOTS;i++) {
        _timeslots[i]->setTimeSlot(_eC.timeSlots[i]);
    }
}

IPAddress EEPROMConfig::getIPAddress() {
    return _eC.ipAddrSetting;
}

void EEPROMConfig::setIPAddress(IPAddress ip) {
    _eC.ipAddrSetting=ip;
}

int EEPROMConfig::getPort() {
    return _eC.portSetting;
}

void EEPROMConfig::setPort(int port) {
    _eC.portSetting = port;
}

String EEPROMConfig::getSSID() {
    return _eC.ssidSetting;
}

void EEPROMConfig::setSSID(String ssid) {
    _eC.ssidSetting = ssid;
}

String EEPROMConfig::getPassword() {
    return _eC.passwordSetting;
}

void EEPROMConfig::setPassword(String password) {
    _eC.passwordSetting = password;
}

bool EEPROMConfig::getNTPEnabled() {
    return _eC.ntpEnabledSetting;
}

void EEPROMConfig::setNTPEnabled(bool ntpEnabled) {
    _eC.ntpEnabledSetting = ntpEnabled;
}

short EEPROMConfig::getGMTOffset() {
    return _eC.gmtOffsetSetting;
}

void EEPROMConfig::setGMTOffset(short gmtOffset) {
    _eC.gmtOffsetSetting = gmtOffset;
}

bool EEPROMConfig::getTimerEnabled() {
    return _eC.timerEnabledSetting;
}

void EEPROMConfig::setTimerEnabled(bool timerEnabled) {
    _eC.timerEnabledSetting = timerEnabled;
}

short EEPROMConfig::getLEDSetting() {
    return _eC.ledSetting;
}

void EEPROMConfig::setLEDSetting(short ledSetting) {
    _eC.ledSetting = ledSetting;
}

bool EEPROMConfig::getRelayManualSetting() {
    return _eC.relayManualSetting;
}

void EEPROMConfig::setRelayManualSetting(bool relayManualSetting) {
    _eC.relayManualSetting = relayManualSetting;
}

timeSlot& EEPROMConfig::getTimeSlot(int index) {
    return _eC.timeSlots[index];
}