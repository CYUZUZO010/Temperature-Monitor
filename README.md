# SPEES402 - Practical A: Temperature Display & MQTT Monitoring

## System Flow
```
[LM35 Sensor] --> [Arduino Uno] --> [I2C LCD 16x2]
                       |
                  [USB Serial]
                       |
                  [PC Python Script]
                       |
                  [MQTT Broker on VPS]
```

## Wiring
| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| LM35 VCC  | +   | 5V          |
| LM35 GND  | -   | GND         |
| LM35 OUT  | Signal | A0       |
| LCD VCC   | +   | 5V          |
| LCD GND   | -   | GND         |
| LCD SDA   | Data | A4 (SDA)  |
| LCD SCL   | Clock | A5 (SCL) |

## Libraries Needed
### Arduino IDE (Install via Library Manager):
- `LiquidCrystal_I2C` by Frank de Brabander

### Python (Install via pip):
```bash
pip install pyserial paho-mqtt
```

## How to Run
1. Upload `temperature_lcd.ino` to Arduino via Arduino IDE
2. Change `SERIAL_PORT` in `pc_monitor.py` to your port (e.g. COM3 or /dev/ttyUSB0)
3. Change `MQTT_BROKER` to your VPS IP address
4. Change `MQTT_TOPIC` to include your candidate name
5. Run: `python pc_monitor.py`

## Serial Data Format
```
25.4,NORMAL
36.1,HIGH
12.0,LOW
```

## MQTT Topic Format
```
spees402/temperature/your_candidate_name
```
