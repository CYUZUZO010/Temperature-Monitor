# Temperature Monitoring System using Arduino, MQTT and VPS

## Candidate Information

**Candidate Name:** Cyuzuzo

**Module:** SPEES402 - Embedded Systems Practical

---

## Project Overview

This project implements a real-time temperature monitoring system using:

- LM35 Temperature Sensor
- Arduino Uno
- 16x2 I2C LCD Display
- Python Serial Monitor
- MQTT Protocol
- VPS-hosted MQTT Broker

The system reads temperature values from the LM35 sensor, displays them on the LCD screen, sends them to a PC through USB serial communication, and publishes them to an MQTT broker hosted on a VPS.

---

## System Architecture

```text
┌─────────────────┐
│   LM35 Sensor   │
└────────┬────────┘
         │ Analog Signal
         ▼
┌─────────────────┐
│   Arduino Uno   │
│                 │
│ Reads Sensor    │
│ Displays LCD    │
│ Sends Serial    │
└────────┬────────┘
         │ USB Serial
         ▼
┌─────────────────┐
│   Python App    │
│ (pc_monitor.py) │
└────────┬────────┘
         │ MQTT Publish
         ▼
┌─────────────────┐
│ MQTT Broker VPS │
│157.173.101.159  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Web Dashboard   │
│ dashboard.html  │
└─────────────────┘
```

---

## Data Flow

```text
LM35
  ↓
Arduino Uno
  ↓
16x2 LCD Display
  ↓
USB Serial Communication
  ↓
Python Monitoring Program
  ↓
MQTT Broker (VPS)
  ↓
Web Dashboard
```

---

## Hardware Components

| Component | Quantity |
|------------|----------|
| Arduino Uno | 1 |
| LM35 Temperature Sensor | 1 |
| I2C LCD 16x2 Display | 1 |
| USB Cable | 1 |
| Computer | 1 |
| VPS MQTT Broker | 1 |

---

## Hardware Connections

### LM35 Sensor

| LM35 Pin | Arduino Uno |
|-----------|-------------|
| VCC | 5V |
| OUT | A0 |
| GND | GND |

### I2C LCD Display

| LCD Pin | Arduino Uno |
|----------|------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

---

## Software Components

### Arduino Program

File:

```text
temperature_lcd.ino
```

Functions:

- Read LM35 temperature
- Display candidate name
- Scroll candidate name if longer than 16 characters
- Display temperature
- Send temperature through serial communication

---

### Python Program

File:

```text
pc_monitor.py
```

Functions:

- Read serial data from Arduino
- Display temperature in real-time
- Publish temperature to MQTT broker

---

### Dashboard

File:

```text
dashboard.html
```

Functions:

- Display received temperature values
- Visual monitoring interface

---

## Communication Technologies

### Arduino ↔ PC

```text
Protocol: Serial Communication
Baud Rate: 9600
Connection: USB
```

### PC ↔ VPS

```text
Protocol: MQTT
Port: 1883
```

---

## MQTT Configuration

### Broker

```text
157.173.101.159
```

### Topic

```text
spees402/temperature/cyuzuzo
```

---

## Serial Data Format

Example:

```text
25.4,NORMAL
28.1,NORMAL
37.2,HIGH
12.3,LOW
```

---

## Python Libraries

Install:

```bash
pip install pyserial
pip install paho-mqtt
```

---

## Running the Project

### 1. Upload Arduino Program

Open Arduino IDE and upload:

```text
temperature_lcd.ino
```

### 2. Configure Python

Edit:

```python
SERIAL_PORT = "COM3"
MQTT_BROKER = "157.173.101.159"
MQTT_TOPIC = "spees402/temperature/cyuzuzo"
```

### 3. Start Monitoring

```bash
python pc_monitor.py
```

---

## Expected Output

LCD:

```text
Cyuzuzo
Temp: 25.4°C
```

Terminal:

```text
[10:12:38] Temperature: 25.4°C | Status: NORMAL
```

MQTT Payload:

```text
25.4,NORMAL
```

---

## Repository Structure

```text
Temperature-Monitor/
│
├── temperature_lcd.ino
├── pc_monitor.py
├── dashboard.html
├── README.md
└── screenshots/
```

---

## Author

Cyuzuzo

SPEES402 Embedded Systems Practical