# Comandi OBD2 - BMW F20

## 📖 Introduzione

Questo documento elenca i PID (Parameter IDs) OBD2 supportati per la BMW F20, come leggerli e interpretarli.

## 🔍 Comandi Supportati

### Motore - Giri e Velocità

| PID | Comando | Descrizione | Unità | Formula |
|-----|---------|-------------|-------|----------|
| 0x0C | `01 0C` | RPM motore | RPM | ((A×256)+B)/4 |
| 0x0D | `01 0D` | Velocità veicolo | km/h | A |
| 0x0E | `01 0E` | Anticipo accensione | ° | (A/2)-64 |

### Motore - Temperature

| PID | Comando | Descrizione | Unità | Formula |
|-----|---------|-------------|-------|----------|
| 0x05 | `01 05` | Temp. liquido raffreddamento | °C | A-40 |
| 0x46 | `01 46` | Temp. aria ambiente | °C | A-40 |
| 0x0F | `01 0F` | Temp. aria aspirazione | °C | A-40 |

### Motore - Carico e Pressione

| PID | Comando | Descrizione | Unità | Formula |
|-----|---------|-------------|-------|----------|
| 0x04 | `01 04` | Carico motore | % | (A/255)×100 |
| 0x10 | `01 10` | Portata aria (MAF) | g/s | ((A×256)+B)/100 |
| 0x0A | `01 0A` | Pressione carburante | kPa | A×3 |

### Carburante

| PID | Comando | Descrizione | Unità | Formula |
|-----|---------|-------------|-------|----------|
| 0x2F | `01 2F` | Livello carburante | % | (A/255)×100 |
| 0x5E | `01 5E` | Posizione pedale gas | % | (A/255)×100 |

### Batteria

| PID | Comando | Descrizione | Unità | Formula |
|-----|---------|-------------|-------|----------|
| 0x42 | `01 42` | Voltaggio batteria | V | ((A×256)+B)/1000 |

## 🚨 Codici Diagnostici (DTC)

### Lettura DTC
```
Comando: 19 02
Risposta: 59 02 [DTC Data]
```

### Cancellazione DTC
```
Comando: 04
```

### Formato DTC BMW

| Prefisso | Significato |
|----------|------------|
| P | Powertrain (Motore) |
| C | Chassis |
| B | Body (Carrozzeria) |
| U | Network (Rete) |

**Esempi:**
- `P0101` - MAF (Portata aria) fuori range
- `P0300` - Misfire rilevato (accensione irregolare)
- `P0335` - Sensore RPM difettoso

## 📝 Esempi di Utilizzo

### Lettura RPM
```
Invio:  01 0C
Risposta: 41 0C 10 2A
Calcolo: RPM = ((0x10 × 256) + 0x2A) / 4 = (4096 + 42) / 4 = 1034.5 RPM
```

### Lettura Velocità
```
Invio:  01 0D
Risposta: 41 0D 46
Calcolo: Velocità = 0x46 = 70 km/h
```

### Lettura Temperatura Motore
```
Invio:  01 05
Risposta: 41 05 6E
Calcolo: Temp = 0x6E - 40 = 110 - 40 = 70°C
```

### Lettura Livello Carburante
```
Invio:  01 2F
Risposta: 41 2F CC
Calcolo: Livello = (0xCC / 255) × 100 = (204 / 255) × 100 = 80%
```

## 🔧 Comandi AT ELM327

| Comando | Descrizione |
|---------|------------|
| `AT Z` | Reset completo |
| `AT E0` | Echo off |
| `AT L0` | Linefeed off |
| `AT S0` | Spaces off |
| `AT SP 6` | CAN 11bit 500k |
| `AT DM1` | Display memory |
| `AT RV` | Leggi voltaggio batteria |

## 📊 Intervalli Normali BMW F20

| Parametro | Min | Normale | Max | Unità |
|-----------|-----|---------|-----|-------|
| RPM Idle | 600 | 800 | 1200 | RPM |
| Velocità | 0 | - | 240 | km/h |
| Temp. Motore | 80 | 90 | 110 | °C |
| Livello Carburante | 0 | - | 100 | % |
| Voltaggio Batteria | 11.5 | 14 | 14.5 | V |
| MAF | - | 3-8 | 20 | g/s |

## ⚠️ Note Importanti

1. **Motore spento**: Alcuni PID richiedono il motore acceso
2. **Timeout**: Se nessuna risposta in 1-2 secondi, il PID potrebbe non essere supportato
3. **BMW F20 specifico**: La F20 supporta sia OBD2 standard che comandi BMW proprietari
4. **Polling rate**: Non leggere più di 1 PID al secondo

## 🔗 Risorse

- [OBD2 Standard Wikipedia](https://en.wikipedia.org/wiki/OBD-II_PIDs)
- [ELM327 Manual](https://www.elmelectronics.com/)
- [BMW F20 Technical Documentation](https://www.bmw.com/)