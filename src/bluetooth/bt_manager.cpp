#include "bt_manager.h"
#include "../utils/logger.h"

extern Logger logger;

BluetoothManager::BluetoothManager() 
    : rxPin(0), txPin(0), baudRate(9600), connected(false), lastConnectionTime(0)
{
}

BluetoothManager::~BluetoothManager()
{
    disconnect();
}

void BluetoothManager::init(uint8_t rxPin, uint8_t txPin, uint32_t baudRate)
{
    this->rxPin = rxPin;
    this->txPin = txPin;
    this->baudRate = baudRate;
    
    logger.info("Bluetooth Manager inizializzato - RX:%d TX:%d BAUD:%d", 
                rxPin, txPin, baudRate);
}

void BluetoothManager::connect(String deviceName)
{
    this->deviceName = deviceName;
    logger.info("Connessione Bluetooth a: %s", deviceName.c_str());
    
    // Inizia UART
    Serial2.begin(baudRate, SERIAL_8N1, rxPin, txPin);
    
    // Attendi connessione
    unsigned long startTime = millis();
    while (millis() - startTime < 10000)
    {
        delay(100);
        if (available())
        {
            String response = readLine();
            if (response.indexOf("OK") >= 0)
            {
                connected = true;
                lastConnectionTime = millis();
                logger.info("Bluetooth connesso");
                return;
            }
        }
    }
    
    logger.warn("Timeout connessione Bluetooth");
}

void BluetoothManager::disconnect()
{
    Serial2.end();
    connected = false;
    logger.info("Bluetooth disconnesso");
}

bool BluetoothManager::isConnected()
{
    return connected && (millis() - lastConnectionTime < 30000);
}

void BluetoothManager::reconnect()
{
    disconnect();
    delay(1000);
    connect(deviceName);
}

void BluetoothManager::sendData(String data)
{
    if (Serial2.availableForWrite())
    {
        Serial2.println(data);
        logger.debug("BT TX: %s", data.c_str());
    }
}

void BluetoothManager::sendCommand(String cmd)
{
    sendData(cmd);
}

String BluetoothManager::readLine()
{
    String line = "";
    unsigned long timeout = millis() + 1000;
    
    while (millis() < timeout)
    {
        if (Serial2.available())
        {
            char c = Serial2.read();
            if (c == '\n')
            {
                break;
            }
            if (c != '\r')
            {
                line += c;
            }
            timeout = millis() + 500;  // Reset timeout ad ogni carattere
        }
    }
    
    if (line.length() > 0)
    {
        lastConnectionTime = millis();
        rxBuffer = line;
    }
    
    return line;
}

bool BluetoothManager::available()
{
    return Serial2.available() > 0;
}

void BluetoothManager::handleCommand(String cmd)
{
    // Rimuovi prefisso "CMD:"
    String command = cmd.substring(4);
    
    logger.debug("Comando ricevuto: %s", command.c_str());
    
    if (command == "STATUS")
    {
        sendData("STATUS:OK");
    }
    else if (command == "RESET")
    {
        sendData("RESET:ACK");
        delay(100);
        ESP.restart();
    }
    else if (command.startsWith("SET_"))
    {
        // Gestisci comando di configurazione
        logger.info("Comando configurazione: %s", command.c_str());
        sendData("SET:OK");
    }
    else
    {
        logger.warn("Comando sconosciuto: %s", command.c_str());
        sendData("ERR:UNKNOWN");
    }
}