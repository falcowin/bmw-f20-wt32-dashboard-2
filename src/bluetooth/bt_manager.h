#ifndef BT_MANAGER_H
#define BT_MANAGER_H

#include <Arduino.h>

class BluetoothManager
{
public:
    BluetoothManager();
    ~BluetoothManager();

    // Inizializzazione
    void init(uint8_t rxPin, uint8_t txPin, uint32_t baudRate);
    void connect(String deviceName);
    void disconnect();
    bool isConnected();
    void reconnect();

    // Comunicazione
    void sendData(String data);
    void sendCommand(String cmd);
    String readLine();
    bool available();

    // Gestione comandi
    void handleCommand(String cmd);

private:
    uint8_t rxPin;
    uint8_t txPin;
    uint32_t baudRate;
    bool connected;
    unsigned long lastConnectionTime;
    String deviceName;

    // Buffer ricezione
    String rxBuffer;
    const size_t MAX_BUFFER_SIZE = 256;
};

#endif // BT_MANAGER_H