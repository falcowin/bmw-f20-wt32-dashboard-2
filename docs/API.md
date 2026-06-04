# API Documentation - BMW F20 Dashboard

## 📌 Panoramica

Questo documento descrive tutte le classi e i metodi principali del progetto.

## 🎮 GUIManager

Gestisce l'interfaccia grafica con LVGL.

### Metodi Principali

```cpp
void init()
```
Inizia il manager della GUI e il display.

```cpp
void showMainScreen()
```
Visualizza la schermata principale con 4 widget (RPM, Velocità, Temperatura, Carburante).

```cpp
void updateMainScreen(uint16_t rpm, uint8_t speed, uint8_t coolantTemp, 
                     int8_t airTemp, uint8_t fuelLevel, float voltage)
```
Aggiorna tutti i widget della schermata principale.

**Parametri:**
- `rpm`: Giri motore (0-7500)
- `speed`: Velocità veicolo (0-240 km/h)
- `coolantTemp`: Temperatura liquido di raffreddamento (0-130°C)
- `airTemp`: Temperatura aria ambiente (-40 a 85°C)
- `fuelLevel`: Livello carburante (0-100%)
- `voltage`: Voltaggio batteria (10-15V)

## 🔌 OBD2Manager

Gestisce la comunicazione OBD2 tramite ELM327.

### Metodi Principali

```cpp
void init()
```
Inizia il manager OBD2.

```cpp
uint16_t getRPM()
```
Legge i giri del motore. **Ritorno:** RPM (0-7500)

```cpp
uint8_t getSpeed()
```
Legge la velocità del veicolo. **Ritorno:** Velocità in km/h (0-240)

```cpp
bool isConnected()
```
Verifica se OBD2 è connesso e responsivo.

## 📡 BluetoothManager

Gestisce la comunicazione Bluetooth con ELM327.

### Metodi Principali

```cpp
void init(uint8_t rxPin, uint8_t txPin, uint32_t baudRate)
```
Inizia la comunicazione seriale per Bluetooth.

```cpp
bool isConnected()
```
Verifica lo stato della connessione.

## 📝 Logger

Sistema di logging con livelli di debug.

### Metodi Principali

```cpp
void init(bool serialDebug, uint8_t debugLevel)
```
Inizia il logger.

```cpp
void info(const char* format, ...)
```
Log informazione (livello 2).

```cpp
void debug(const char* format, ...)
```
Log debug (livello 3).

---

**Ultimo aggiornamento**: 2026-06-04
**Versione**: 1.0.0