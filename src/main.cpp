#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "config.h"
#include "display/gui.h"
#include "obd2/obd2_manager.h"
#include "bluetooth/bt_manager.h"
#include "utils/logger.h"

// Variabili globali
OBD2Manager obd2Manager;
BluetoothManager btManager;
GUIManager guiManager;
Logger logger;

// Task handles
TaskHandle_t obd2TaskHandle = NULL;
TaskHandle_t guiTaskHandle = NULL;
TaskHandle_t btTaskHandle = NULL;

// ===== PROTOTIPI FUNZIONI =====
void setupDisplay();
void setupSerial();
void setupBluetooth();
void setupOBD2();
void obd2Task(void *parameter);
void guiTask(void *parameter);
void bluetoothTask(void *parameter);

// ===== SETUP =====
void setup()
{
    // Inizializza Serial
    setupSerial();
    logger.init(SERIAL_DEBUG, DEBUG_LEVEL);
    logger.info("Avvio BMW F20 Dashboard...");

    // Inizializza display
    logger.info("Inizializzazione display...");
    setupDisplay();

    // Inizializza Bluetooth
    if (BT_ENABLED)
    {
        logger.info("Inizializzazione Bluetooth...");
        setupBluetooth();
    }

    // Inizializza OBD2
    logger.info("Inizializzazione OBD2...");
    setupOBD2();

    // Crea task per CPU1
    logger.info("Creazione task RTOS...");
    
    xTaskCreatePinnedToCore(
        obd2Task,           // Funzione task
        "OBD2Task",         // Nome
        4096,               // Stack size
        NULL,               // Parametri
        2,                  // Priorità
        &obd2TaskHandle,    // Task handle
        1                   // Core 1
    );

    xTaskCreatePinnedToCore(
        bluetoothTask,
        "BluetoothTask",
        4096,
        NULL,
        2,
        &btTaskHandle,
        1
    );

    xTaskCreatePinnedToCore(
        guiTask,
        "GUITask",
        8192,
        NULL,
        1,
        &guiTaskHandle,
        0
    );

    logger.info("Sistema avviato correttamente!");
}

// ===== LOOP PRINCIPALE =====
void loop()
{
    delay(1000);
    
    // Monitoraggio memoria
    if (logger.getDebugLevel() >= 3)
    {
        uint32_t freeRam = ESP.getFreeHeap();
        logger.debug("Free RAM: %u bytes", freeRam);
    }
}

// ===== FUNZIONI SETUP =====
void setupSerial()
{
    Serial.begin(115200);
    delay(100);
}

void setupDisplay()
{
    guiManager.init();
    guiManager.showSplashScreen();
    delay(2000);
    guiManager.showMainScreen();
}

void setupBluetooth()
{
    btManager.init(UART_RX_PIN, UART_TX_PIN, UART_SPEED);
    btManager.connect(BT_DEVICE_NAME);
}

void setupOBD2()
{
    obd2Manager.init();
    obd2Manager.setMode(OBD2_MODE);
}

// ===== TASK RTOS =====

/**
 * Task per gestione OBD2
 * Legge i dati dal modulo OBD2 a intervalli regolari
 */
void obd2Task(void *parameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(OBD2_POLL_RATE);

    logger.info("OBD2 Task avviato");

    while (1)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // Leggi dati OBD2
        if (obd2Manager.isConnected())
        {
            // Leggi RPM
            uint16_t rpm = obd2Manager.getRPM();
            
            // Leggi velocità
            uint8_t speed = obd2Manager.getSpeed();
            
            // Leggi temperatura motore
            uint8_t coolantTemp = obd2Manager.getCoolantTemp();
            
            // Leggi temperatura aria
            int8_t airTemp = obd2Manager.getAmbientAirTemp();
            
            // Leggi livello carburante
            uint8_t fuelLevel = obd2Manager.getFuelLevel();
            
            // Leggi voltaggio batteria
            float voltage = obd2Manager.getBatteryVoltage();

            // Aggiorna GUI con i nuovi dati
            guiManager.updateMainScreen(rpm, speed, coolantTemp, airTemp, fuelLevel, voltage);

            // Log dati
            if (SD_LOG_ENABLED)
            {
                logger.logData(rpm, speed, coolantTemp, fuelLevel);
            }

            // Debug
            if (logger.getDebugLevel() >= 2)
            {
                logger.debug("RPM: %d | Speed: %d km/h | Temp: %d°C | Fuel: %d%% | Voltage: %.1fV",
                           rpm, speed, coolantTemp, fuelLevel, voltage);
            }
        }
        else
        {
            logger.warn("OBD2 non connesso");
            guiManager.showConnectionError();
        }
    }
}

/**
 * Task per gestione Bluetooth
 * Mantiene la connessione Bluetooth attiva
 */
void bluetoothTask(void *parameter)
{
    logger.info("Bluetooth Task avviato");

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));

        if (!btManager.isConnected())
        {
            logger.warn("Bluetooth disconnesso, tentativo riconnessione...");
            btManager.reconnect();
        }

        // Elabora dati ricevuti
        if (btManager.available())
        {
            String data = btManager.readLine();
            logger.debug("BT RX: %s", data.c_str());
            
            // Elabora comando
            if (data.startsWith("CMD:"))
            {
                btManager.handleCommand(data);
            }
        }
    }
}

/**
 * Task per gestione GUI
 * Aggiorna l'interfaccia grafica
 */
void guiTask(void *parameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000 / 30);  // 30 FPS

    logger.info("GUI Task avviato");

    while (1)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // Aggiorna display
        guiManager.update();

        // Elabora input touch
        guiManager.handleInput();
    }
}