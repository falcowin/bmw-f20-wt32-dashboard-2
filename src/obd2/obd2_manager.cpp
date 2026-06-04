#include "obd2_manager.h"
#include "../utils/logger.h"

extern Logger logger;

OBD2Manager::OBD2Manager() : connected(false), lastResponseTime(0)
{
    memset(&cachedData, 0, sizeof(cachedData));
}

OBD2Manager::~OBD2Manager()
{
    disconnect();
}

void OBD2Manager::init()
{
    logger.info("Inizializzazione OBD2 Manager");
    elm327.init();
}

void OBD2Manager::setMode(String mode)
{
    this->mode = mode;
    logger.info("OBD2 Mode impostato a: %s", mode.c_str());
}

void OBD2Manager::connect()
{
    if (elm327.begin() == 1)
    {
        connected = true;
        logger.info("OBD2 connesso con successo");
    }
    else
    {
        connected = false;
        logger.error("Errore connessione OBD2");
    }
}

void OBD2Manager::disconnect()
{
    elm327.end();
    connected = false;
}

bool OBD2Manager::isConnected()
{
    return connected && (millis() - lastResponseTime < 5000);
}

uint16_t OBD2Manager::getRPM()
{
    if (elm327.queryPID(0x0C))  // PID_RPM
    {
        cachedData.rpm = elm327.getRPM();
        lastResponseTime = millis();
    }
    return cachedData.rpm;
}

uint8_t OBD2Manager::getSpeed()
{
    if (elm327.queryPID(0x0D))  // PID_SPEED
    {
        cachedData.speed = elm327.getSpeed();
        lastResponseTime = millis();
    }
    return cachedData.speed;
}

uint8_t OBD2Manager::getCoolantTemp()
{
    if (elm327.queryPID(0x05))  // PID_COOLANT_TEMP
    {
        cachedData.coolantTemp = elm327.getCoolantTemperature();
        lastResponseTime = millis();
    }
    return cachedData.coolantTemp;
}

int8_t OBD2Manager::getAmbientAirTemp()
{
    if (elm327.queryPID(0x46))  // PID_AIR_TEMP
    {
        cachedData.ambientTemp = elm327.getAmbientAirTemperature();
        lastResponseTime = millis();
    }
    return cachedData.ambientTemp;
}

uint8_t OBD2Manager::getFuelLevel()
{
    if (elm327.queryPID(0x2F))  // PID_FUEL_LEVEL
    {
        cachedData.fuelLevel = elm327.getFuelLevel();
        lastResponseTime = millis();
    }
    return cachedData.fuelLevel;
}

float OBD2Manager::getBatteryVoltage()
{
    // BMW F20 utilizza PID non standard per voltaggio batteria
    // Leggi tramite comando AT (AT EV per voltaggio)
    String response;
    if (sendAndReceive("AT EV", response))
    {
        // Parsing risposta voltaggio
        float voltage = response.toFloat();
        cachedData.voltage = voltage;
        lastResponseTime = millis();
    }
    return cachedData.voltage;
}

uint16_t OBD2Manager::getFuelPressure()
{
    if (elm327.queryPID(0x0A))  // PID_FUEL_PRESSURE
    {
        cachedData.fuelPressure = elm327.getFuelPressure();
        lastResponseTime = millis();
    }
    return cachedData.fuelPressure;
}

uint8_t OBD2Manager::getEngineLoad()
{
    if (elm327.queryPID(0x04))  // PID_ENGINE_LOAD
    {
        cachedData.engineLoad = elm327.getEngineLoad();
        lastResponseTime = millis();
    }
    return cachedData.engineLoad;
}

int8_t OBD2Manager::getTimingAdvance()
{
    if (elm327.queryPID(0x0E))  // PID_TIMING_ADVANCE
    {
        cachedData.timingAdvance = elm327.getTimingAdvance();
        lastResponseTime = millis();
    }
    return cachedData.timingAdvance;
}

float OBD2Manager::getMAFAirflow()
{
    if (elm327.queryPID(0x10))  // PID_MAF_AIRFLOW
    {
        cachedData.mafAirflow = elm327.getMAFAirflow();
        lastResponseTime = millis();
    }
    return cachedData.mafAirflow;
}

void OBD2Manager::readDTC()
{
    String response;
    if (sendAndReceive("19 02", response))  // Leggi DTC confermati
    {
        cachedData.dtcCode = response;
        cachedData.engineLight = !response.isEmpty();
        lastResponseTime = millis();
        logger.info("DTC: %s", cachedData.dtcCode.c_str());
    }
}

String OBD2Manager::getDTCCode()
{
    return cachedData.dtcCode;
}

void OBD2Manager::clearDTC()
{
    sendCommand("04");  // Comando per cancellare DTC
    logger.info("DTC cancellati");
}

bool OBD2Manager::checkEngineLight()
{
    return cachedData.engineLight;
}

void OBD2Manager::sendCommand(String cmd)
{
    elm327.sendCommand(cmd.c_str());
}

String OBD2Manager::readResponse()
{
    return String(elm327.response);
}

void OBD2Manager::resetConnection()
{
    logger.warn("Reset connessione OBD2");
    disconnect();
    delay(1000);
    connect();
}

bool OBD2Manager::sendAndReceive(String command, String &response)
{
    elm327.sendCommand(command.c_str());
    delay(100);
    
    if (elm327.queryPID(command.charAt(0)))
    {
        response = String(elm327.response);
        return true;
    }
    return false;
}