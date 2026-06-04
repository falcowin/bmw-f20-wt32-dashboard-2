# BMW F20 WT32-SC01 Plus Dashboard

Interfaccia grafica completa per visualizzare i dati diagnostici della BMW F20 su display WT32-SC01 Plus con ESP32.

## 🚗 Caratteristiche

- **Lettura dati BMW F20** via OBD2 (Bluetooth/Wi-Fi)
- **Interfaccia touch intuitiva** con LVGL
- **Visualizzazione in tempo reale**:
  - RPM e velocità
  - Temperatura motore/olio
  - Consumo carburante
  - Voltaggio batteria
  - Codici diagnostici (DTC)
- **Storage dati** su SD card
- **Menu navigazione** completo
- **Configurazione wireless**

## 📱 Hardware Richiesto

- **WT32-SC01 Plus** (Display 3.5" ESP32)
- **Lettore OBD2 Bluetooth** (es. ELM327)
- **Cavo USB** per programmazione
- **Alimentazione 12V** (da accendisigari auto)
- **SD card** (opzionale, per logging)

## 🔧 Installazione

### 1. Prerequisiti
```bash
# Installa PlatformIO
pip install platformio

# Clona il repository
git clone https://github.com/falcowin/bmw-f20-wt32-dashboard-2.git
cd bmw-f20-wt32-dashboard-2
```

### 2. Configurazione
- Modifica `src/config.h` con i tuoi parametri Wi-Fi
- Configura il modulo OBD2 in `src/obd2_manager.cpp`

### 3. Build e Upload
```bash
pio run -t upload
```

## 📁 Struttura Progetto

```
bmw-f20-wt32-dashboard-2/
├── platformio.ini           # Configurazione PlatformIO
├── src/
│   ├── main.cpp            # Entry point principale
│   ├── config.h            # Configurazioni globali
│   ├── display/
│   │   ├── gui.cpp         # Interfaccia grafica LVGL
│   │   └── gui.h
│   ├── obd2/
│   │   ├── obd2_manager.cpp # Gestione OBD2
│   │   ├── obd2_manager.h
│   │   ├── elm327.cpp       # Driver ELM327
│   │   └── elm327.h
│   ├── bluetooth/
│   │   ├── bt_manager.cpp   # Gestione Bluetooth
│   │   └── bt_manager.h
│   └── utils/
│       ├── logger.cpp       # Sistema logging
│       └── logger.h
├── docs/
│   ├── INSTALL.md          # Guida installazione
│   ├── API.md              # Documentazione API
│   └── OBD2_COMMANDS.md    # Comandi OBD2
└── .gitignore
```

## 🔌 Connessioni Hardware

### WT32-SC01 Plus - OBD2 Bluetooth
```
WT32 UART0 (RX/TX) ← → ELM327 Bluetooth Module
GPIO16 (RX)        ← → TX
GPIO17 (TX)        ← → RX
GND                ← → GND
```

## 📊 Comandi OBD2 Supportati

| Comando | Descrizione |
|---------|-------------|
| `01 0C` | RPM (giri motore) |
| `01 0D` | Velocità |
| `01 05` | Temperatura liquido |
| `01 46` | Temperatura aria ambiente |
| `01 10` | Portata aria |
| `01 2F` | Livello carburante |
| `01 42` | Voltaggio batteria |
| `19 02` | Codici guasto (DTC) |

## 🎮 Uso

1. **Accendi il display**: automaticamente si connette all'OBD2
2. **Schermata principale**: visualizza dati tempo reale
3. **Menu**: swipe left/right per navigare
4. **Settings**: configura connessione e visualizzazione

## 📝 Configurazione Iniziale

### src/config.h
```cpp
#define WIFI_SSID "TuoSSID"
#define WIFI_PASSWORD "TuaPassword"
#define OBD2_MODE "BLUETOOTH"  // o "WIFI"
#define OBD2_DEVICE "HC-05"    // Nome dispositivo
```

## 🐛 Troubleshooting

**Il display non si accende**
- Verifica alimentazione 12V
- Controlla cavo USB

**Nessuna connessione OBD2**
- Verifica accoppiamento Bluetooth
- Controlla spazi UART

**Dati non visualizzati**
- Avvia il motore (alcuni dati richiedono motore acceso)
- Verifica comandi OBD2 supportati

## 📚 Documentazione

- [Guida Installazione](docs/INSTALL.md)
- [Documentazione API](docs/API.md)
- [Comandi OBD2](docs/OBD2_COMMANDS.md)

## 🤝 Contributi

Segnalazioni e pull request sono benvenuti!

## 📄 Licenza

MIT License

## ⚠️ Disclaimer

Questo software è fornito "così com'è" per scopi educativi. L'uso su strada è a rischio dell'utente.

---

**Creato per**: BMW F20 + WT32-SC01 Plus
**Autore**: falcowin
**Ultimo aggiornamento**: 2026-06-04