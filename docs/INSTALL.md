# Guida di Installazione

## 📋 Prerequisiti

### Software
- **PlatformIO Core** (`pip install platformio`)
- **Python 3.8+**
- **Git**

### Hardware
- **WT32-SC01 Plus**
- **ELM327 Bluetooth** (HC-05 o simile)
- **Cavo USB Mini**
- **Cavetti Jumper**

## 🔧 Configurazione Hardware

### Connessioni ELM327 ← → WT32-SC01

```
ELM327           WT32-SC01
VCC      ----→   5V
GND      ----→   GND
TX       ----→   GPIO16 (RX)
RX       ----→   GPIO17 (TX)
```

### Alimentazione
Il WT32-SC01 Plus accetta:
- **USB Mini** (5V per programmazione)
- **12V Auto** (via regolatore)

## 📥 Installazione Repository

### 1. Clone il repository
```bash
git clone https://github.com/falcowin/bmw-f20-wt32-dashboard-2.git
cd bmw-f20-wt32-dashboard-2
```

### 2. Installa dipendenze
```bash
pip install platformio
pio pkg install
```

### 3. Configurazione `src/config.h`
Modifica le seguenti impostazioni:

```cpp
// Wi-Fi (opzionale)
#define WIFI_SSID "TuoSSID"
#define WIFI_PASSWORD "TuaPassword"

// Bluetooth
#define BT_DEVICE_NAME "HC-05"

// OBD2
#define OBD2_MODE "BLUETOOTH"  // Usa BLUETOOTH per HC-05

// Debug
#define SERIAL_DEBUG 1
#define DEBUG_LEVEL 2  // 0=OFF, 1=ERROR, 2=INFO, 3=DEBUG
```

## 🚀 Build e Upload

### Build
```bash
pio run
```

### Upload sul dispositivo
```bash
pio run -t upload
```

### Monitor Serial
```bash
pio device monitor -b 115200
```

## ✅ Verifica Installazione

Dopo l'upload, dovresti vedere:

```
[INFO] [12:34:56]: Avvio BMW F20 Dashboard...
[INFO] [12:35:00]: Inizializzazione display...
[INFO] [12:35:01]: Inizializzazione Bluetooth...
[INFO] [12:35:02]: Inizializzazione OBD2...
[INFO] [12:35:03]: Creazione task RTOS...
[INFO] [12:35:04]: Sistema avviato correttamente!
```

## 🔌 Pairing Bluetooth

### Metodo Manuale
1. Accendi il WT32-SC01 Plus
2. Apri monitor seriale (vedrai l'output)
3. L'HC-05 si dovrebbe accoppiare automaticamente

### Comandi AT per HC-05 (opzionale)
```
AT+NAME=BMW-F20          # Imposta nome
AT+PSWD=1234             # Imposta password
AT+UART=38400,0,0        # Imposta baudrate
```

## 🐛 Troubleshooting

### Il display non si accende
```
✗ Controllare alimentazione 12V
✗ Verificare cavo USB
✗ Premere Reset button
```

### Nessuna connessione OBD2
```
✗ Verificare accoppiamento Bluetooth
✗ Controllare cavi UART (GPIO16/17)
✗ Leggere monitor seriale per errori
```

### Codice di errore durante upload
```bash
# Reset bootloader
pio device monitor --raw
# Tenere premuto BOOT, poi RST durante il caricamento
```

## 📊 Comandi Utili PlatformIO

```bash
# Pulisci build
pio run -t clean

# Ricompila tutto
pio run -t build

# Monitor con filtri
pio device monitor -b 115200 --raw

# Carica OTA (Over-The-Air)
pio run -t upload

# Installa libreria specifica
pio lib install "Nome Libreria"

# Lista dei dispostivi seriali
pio device list
```

## 📚 Riferimenti Utili

- [WT32-SC01 Plus Datasheet](docs/WT32-SC01_PLUS_SPECIFICATIONS.pdf)
- [ELM327 Protocol](docs/ELM327_PROTOCOL.pdf)
- [PlatformIO Docs](https://docs.platformio.org/)
- [LVGL Documentation](https://docs.lvgl.io/)

## 🎯 Prossimi Passi

1. **Accendi il motore** della BMW F20
2. **Connetti l'OBD2** alla porta diagnostica
3. **Osserva i dati** sul display

Buona fortuna! 🚗💻