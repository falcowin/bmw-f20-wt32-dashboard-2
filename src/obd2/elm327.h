#ifndef ELM327_H
#define ELM327_H

#include <Arduino.h>

class ELM327
{
public:
    ELM327();
    
    // Variabili pubbliche
    char response[256];
    
    // Metodi
    void init();
    void end();
    bool begin();
    bool queryPID(uint8_t pid);
    
    // Getters OBD2
    uint16_t getRPM();
    uint8_t getSpeed();
    uint8_t getCoolantTemperature();
    int8_t getAmbientAirTemperature();
    uint8_t getFuelLevel();
    uint16_t getFuelPressure();
    uint8_t getEngineLoad();
    int8_t getTimingAdvance();
    float getMAFAirflow();
    
    // Comandi AT
    void sendCommand(const char* cmd);
    bool readResponse();
    
private:
    // Buffer
    char cmdBuffer[64];
    unsigned long responseTime;
    
    // Metodi privati
    void flushSerial();
    bool sendATCommand(const char* cmd, const char* expectedResponse = "OK");
};

#endif // ELM327_H