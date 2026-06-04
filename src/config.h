#ifndef CONFIG_H
#define CONFIG_H

// ===== CONFIGURAZIONE WIFI =====
#define WIFI_SSID "TuoSSID"
#define WIFI_PASSWORD "TuaPassword"
#define WIFI_TIMEOUT 10000  // ms

// ===== CONFIGURAZIONE BLUETOOTH =====
#define BT_DEVICE_NAME "HC-05"
#define BT_ENABLED 1
#define UART_RX_PIN 16
#define UART_TX_PIN 17
#define UART_SPEED 38400

// ===== CONFIGURAZIONE OBD2 =====
#define OBD2_MODE "BLUETOOTH"  // "BLUETOOTH" o "WIFI"
#define OBD2_POLL_RATE 500     // ms tra le letture
#define OBD2_TIMEOUT 2000      // ms timeout risposta

// ===== CONFIGURAZIONE DISPLAY =====
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320
#define DISPLAY_BPP 16
#define TOUCH_CALIBRATION 1

// ===== CONFIGURAZIONE SD CARD =====
#define SD_CARD_ENABLED 1
#define SD_CS_PIN 5
#define SD_LOG_ENABLED 1
#define LOG_INTERVAL 60000  // ms tra i log

// ===== CONFIGURAZIONE LOGGING =====
#define SERIAL_DEBUG 1
#define DEBUG_LEVEL 2  // 0=OFF, 1=ERROR, 2=INFO, 3=DEBUG
#define MAX_LOG_SIZE 1048576  // 1MB

// ===== CONFIGURAZIONE MOTORE =====
#define ENGINE_TYPE "N20"  // BMW F20
#define OIL_TEMP_OFFSET 0
#define FUEL_TANK_CAPACITY 50  // litri

// ===== PID OBD2 DA LEGGERE =====
#define PID_RPM 0x0C
#define PID_SPEED 0x0D
#define PID_COOLANT_TEMP 0x05
#define PID_AIR_TEMP 0x46
#define PID_MAF_AIRFLOW 0x10
#define PID_FUEL_LEVEL 0x2F
#define PID_VOLTAGE 0x42
#define PID_FUEL_PRESSURE 0x0A
#define PID_ENGINE_LOAD 0x04
#define PID_TIMING_ADVANCE 0x0E

// ===== CONFIGURAZIONE GUI =====
#define GUI_REFRESH_RATE 100  // ms
#define FONT_SIZE_LARGE 48
#define FONT_SIZE_MEDIUM 32
#define FONT_SIZE_SMALL 16

// ===== CONFIGURAZIONE ALLARMI =====
#define ALARM_COOLANT_TEMP_HIGH 110   // °C
#define ALARM_OIL_TEMP_HIGH 120        // °C
#define ALARM_RPM_HIGH 7000            // RPM
#define ALARM_VOLTAGE_LOW 11.0         // V

// ===== CONFIGURAZIONE SALVATAGGIO DATI =====
#define DATA_HISTORY_SIZE 3600  // secondi
#define DATA_SAMPLE_INTERVAL 1000  // ms

// ===== COLORI TEMA =====
#define COLOR_PRIMARY 0x1E90FF      // Blu
#define COLOR_SECONDARY 0xFF6347    // Rosso
#define COLOR_SUCCESS 0x32CD32      // Verde
#define COLOR_WARNING 0xFFD700      // Giallo
#define COLOR_DANGER 0xFF0000       // Rosso scuro
#define COLOR_BG 0x1A1A1A           // Nero
#define COLOR_TEXT 0xFFFFFF         // Bianco

#endif // CONFIG_H