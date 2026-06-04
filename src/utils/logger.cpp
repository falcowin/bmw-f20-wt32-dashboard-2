#include "logger.h"
#include <stdarg.h>

Logger::Logger() : serialDebugEnabled(false), currentDebugLevel(0)
{
}

void Logger::init(bool serialDebug, uint8_t debugLevel)
{
    serialDebugEnabled = serialDebug;
    currentDebugLevel = debugLevel;
    
    if (serialDebugEnabled)
    {
        Serial.println("\n\n========================================");
        Serial.println("   BMW F20 Dashboard - Sistema Log");
        Serial.println("========================================\n");
    }
}

void Logger::error(const char* format, ...)
{
    if (currentDebugLevel >= 1)
    {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        
        logToSerial("[ERROR]", buffer);
    }
}

void Logger::warn(const char* format, ...)
{
    if (currentDebugLevel >= 1)
    {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        
        logToSerial("[WARN]", buffer);
    }
}

void Logger::info(const char* format, ...)
{
    if (currentDebugLevel >= 2)
    {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        
        logToSerial("[INFO]", buffer);
    }
}

void Logger::debug(const char* format, ...)
{
    if (currentDebugLevel >= 3)
    {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        
        logToSerial("[DEBUG]", buffer);
    }
}

void Logger::logToSerial(const char* level, const char* message)
{
    if (serialDebugEnabled)
    {
        // Formato: [HH:MM:SS] [LEVEL] Message
        char logEntry[512];
        snprintf(logEntry, sizeof(logEntry), "[%s] %s: %s", 
                getTimestamp(), level, message);
        
        Serial.println(logEntry);
    }
}

const char* Logger::getTimestamp()
{
    static char timestamp[12];
    unsigned long ms = millis();
    unsigned long seconds = ms / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    
    snprintf(timestamp, sizeof(timestamp), "%02lu:%02lu:%02lu",
            hours % 24, minutes % 60, seconds % 60);
    
    return timestamp;
}

void Logger::logData(uint16_t rpm, uint8_t speed, uint8_t temp, uint8_t fuel)
{
    if (currentDebugLevel >= 2)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), 
                "DATA: RPM=%d Speed=%d Temp=%d Fuel=%d%%",
                rpm, speed, temp, fuel);
        
        logToSerial("[DATA]", buffer);
    }
}

void Logger::logError(String errorMsg)
{
    if (currentDebugLevel >= 1)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "ERROR: %s", errorMsg.c_str());
        
        logToSerial("[ERROR]", buffer);
    }
}