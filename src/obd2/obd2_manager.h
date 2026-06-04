#ifndef OBD2_MANAGER_H
#define OBD2_MANAGER_H

#include <Arduino.h>
#include "elm327.h"

class OBD2Manager
{
public:
    OBD2Manager();
    ~OBD2Manager();

    // Inizializzazione
    void init();
    void setMode(String mode);  // "BLUETOOTH" o "WIFI"
    void connect();
    void disconnect();
    bool isConnected();

    // Lettura PID
    uint16_t getRPM();
    uint8_t getSpeed();
    uint8_t getCoolantTemp();
    int8_t getAmbientAirTemp();
    uint8_t getFuelLevel();
    float getBatteryVoltage();
    uint16_t getFuelPressure();
    uint8_t getEngineLoad();
    int8_t getTimingAdvance();
    float getMAFAirflow();

    // Diagnostica
    void readDTC();                    // Leggi codici guasto
    String getDTCCode();
    void clearDTC();
    bool checkEngineLight();

    // Utilità
    void sendCommand(String cmd);
    String readResponse();
    void resetConnection();

private:
    ELM327 elm327;
    String mode;                       // "BLUETOOTH" o "WIFI"
    bool connected;
    unsigned long lastResponseTime;
    
    // Buffer cache dati
    struct {
        uint16_t rpm;
        uint8_t speed;
        uint8_t coolantTemp;
        int8_t ambientTemp;
        uint8_t fuelLevel;
        float voltage;
        uint16_t fuelPressure;
        uint8_t engineLoad;
        int8_t timingAdvance;
        float mafAirflow;
        String dtcCode;
        bool engineLight;
    } cachedData;

    // Funzioni private
    void updateCache();
    bool sendAndReceive(String command, String &response);
};

#endif // OBD2_MANAGER_H