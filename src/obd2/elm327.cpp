#include "elm327.h"
#include "../utils/logger.h"

extern Logger logger;

ELM327::ELM327() : responseTime(0)
{
    memset(response, 0, sizeof(response));
    memset(cmdBuffer, 0, sizeof(cmdBuffer));
}

void ELM327::init()
{
    logger.info("Inizializzazione ELM327");
}

void ELM327::end()
{
    Serial2.end();
    logger.info("ELM327 chiuso");
}

bool ELM327::begin()
{
    logger.info("Avvio comunicazione ELM327");
    
    // Invia comandi di inizializzazione
    sendATCommand("AT Z", "OK");      // Reset
    delay(500);
    
    sendATCommand("AT E0", "OK");     // Echo off
    sendATCommand("AT L0", "OK");     // Linefeed off
    sendATCommand("AT S0", "OK");     // Spaces off
    sendATCommand("AT SP 6", "OK");   // Protocollo ISO 15765-4 (CAN 11bit)
    
    return true;
}

bool ELM327::queryPID(uint8_t pid)
{
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "01 %02X", pid);
    
    sendCommand(cmd);
    delay(100);
    
    return readResponse();
}

uint16_t ELM327::getRPM()
{
    if (queryPID(0x0C))
    {
        // Parsing risposta: 41 0C AA BB
        // RPM = ((A*256)+B)/4
        uint8_t a = strtol(response + 6, NULL, 16);
        uint8_t b = strtol(response + 9, NULL, 16);
        return ((a * 256) + b) / 4;
    }
    return 0;
}

uint8_t ELM327::getSpeed()
{
    if (queryPID(0x0D))
    {
        // Parsing: 41 0D AA = AA km/h
        return strtol(response + 6, NULL, 16);
    }
    return 0;
}

uint8_t ELM327::getCoolantTemperature()
{
    if (queryPID(0x05))
    {
        // Parsing: 41 05 AA = AA - 40 °C
        uint8_t raw = strtol(response + 6, NULL, 16);
        return raw - 40;
    }
    return 0;
}

int8_t ELM327::getAmbientAirTemperature()
{
    if (queryPID(0x46))
    {
        // Parsing: 41 46 AA = AA - 40 °C
        uint8_t raw = strtol(response + 6, NULL, 16);
        return raw - 40;
    }
    return 0;
}

uint8_t ELM327::getFuelLevel()
{
    if (queryPID(0x2F))
    {
        // Parsing: 41 2F AA = (AA/255)*100 %
        uint8_t raw = strtol(response + 6, NULL, 16);
        return (raw * 100) / 255;
    }
    return 0;
}

uint16_t ELM327::getFuelPressure()
{
    if (queryPID(0x0A))
    {
        // Parsing: 41 0A AA = AA * 3 kPa
        uint8_t raw = strtol(response + 6, NULL, 16);
        return raw * 3;
    }
    return 0;
}

uint8_t ELM327::getEngineLoad()
{
    if (queryPID(0x04))
    {
        // Parsing: 41 04 AA = (AA/255)*100 %
        uint8_t raw = strtol(response + 6, NULL, 16);
        return (raw * 100) / 255;
    }
    return 0;
}

int8_t ELM327::getTimingAdvance()
{
    if (queryPID(0x0E))
    {
        // Parsing: 41 0E AA = (AA/2) - 64 °
        uint8_t raw = strtol(response + 6, NULL, 16);
        return (raw / 2) - 64;
    }
    return 0;
}

float ELM327::getMAFAirflow()
{
    if (queryPID(0x10))
    {
        // Parsing: 41 10 AA BB = ((AA*256)+BB)/100 g/s
        uint8_t a = strtol(response + 6, NULL, 16);
        uint8_t b = strtol(response + 9, NULL, 16);
        return ((a * 256) + b) / 100.0;
    }
    return 0.0;
}

void ELM327::sendCommand(const char* cmd)
{
    flushSerial();
    
    logger.debug("ELM CMD: %s", cmd);
    Serial2.println(cmd);
    
    responseTime = millis();
}

bool ELM327::readResponse()
{
    unsigned long timeout = millis() + 1000;
    memset(response, 0, sizeof(response));
    uint16_t index = 0;
    
    while (millis() < timeout)
    {
        if (Serial2.available())
        {
            char c = Serial2.read();
            
            if (c == '\r' || c == '\n')
            {
                if (index > 0)
                {
                    response[index] = '\0';
                    logger.debug("ELM RX: %s", response);
                    
                    // Verifica se è una risposta valida
                    if (strstr(response, "41") != NULL)  // Risposta positiva
                    {
                        return true;
                    }
                    else if (strstr(response, "NO DATA") != NULL)
                    {
                        logger.warn("ELM: NO DATA");
                        return false;
                    }
                    else if (strstr(response, "?") != NULL)
                    {
                        logger.warn("ELM: Comando non riconosciuto");
                        return false;
                    }
                    
                    index = 0;
                }
            }
            else if (c != ' ')
            {
                response[index++] = c;
            }
            
            timeout = millis() + 200;  // Reset timeout
        }
    }
    
    logger.warn("ELM: Timeout risposta");
    return false;
}

void ELM327::flushSerial()
{
    while (Serial2.available())
    {
        Serial2.read();
    }
    delay(10);
}

bool ELM327::sendATCommand(const char* cmd, const char* expectedResponse)
{
    sendCommand(cmd);
    delay(100);
    
    if (readResponse())
    {
        if (strstr(response, expectedResponse) != NULL)
        {
            logger.debug("ELM AT OK: %s", cmd);
            return true;
        }
    }
    
    logger.warn("ELM AT FAIL: %s", cmd);
    return false;
}