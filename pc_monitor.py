
import serial          # For reading from Arduino via USB serial
import paho.mqtt.client as mqtt  # For publishing to MQTT broker
from datetime import datetime    # For timestamps


SERIAL_PORT = "COM5"         # Change to your port (Linux: /dev/ttyUSB0, Mac: /dev/cu.usbmodem*)
BAUD_RATE = 9600             # Must match Arduino's Serial.begin(9600)
MQTT_BROKER = "broker.benax.rw"  # Using broker.benax.rw as requested
MQTT_PORT = 1883             # Default MQTT port
MQTT_TOPIC = "spees402/temperature/Phoenix"  # Using your name: CYUZUZO


def on_connect(client, userdata, flags, rc):
    """Called when connected to MQTT broker"""
    if rc == 0:
        print(f"[MQTT] Connected to broker at {MQTT_BROKER}")
    else:
        print(f"[MQTT] Connection failed with code {rc}")

# Set up MQTT client
mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect

# Try to connect to MQTT broker
try:
    mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
    mqtt_client.loop_start()  # Start MQTT background thread
except Exception as e:
    print(f"[MQTT] Could not connect: {e}")
    print("[MQTT] Continuing without MQTT publishing...")

# Try to connect to Arduino via Serial
try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"[SERIAL] Connected to Arduino on {SERIAL_PORT}")
except Exception as e:
    print(f"[SERIAL] Could not connect: {e}")
    print(f"[SERIAL] Check your port name. Tried: {SERIAL_PORT}")
    exit()

print("\n" + "="*50)
print("  SPEES402 - Temperature Monitor")
print("="*50)
print(f"  Serial Port : {SERIAL_PORT}")
print(f"  MQTT Topic  : {MQTT_TOPIC}")
print("="*50)
print("  Listening for data... (Ctrl+C to stop)\n")

# Main loop: read from Arduino and publish to MQTT
try:
    while True:
        try:
            # Read one line, ignore decoding errors from serial noise
            raw_data = arduino.readline()
            if not raw_data:
                continue
                
            line = raw_data.decode('utf-8', errors='ignore').strip()

            if line and "," in line:
                parts = line.split(",")

                if len(parts) == 2:
                    temperature = parts[0]
                    status = parts[1]
                    timestamp = datetime.now().strftime("%H:%M:%S")

                    # Print to terminal in a clean format
                    print(f"[{timestamp}]  Temperature: {temperature}°C  |  Status: {status}")

                    # Publish to MQTT broker
                    payload = f"{temperature},{status}"
                    mqtt_client.publish(MQTT_TOPIC, payload)
        except Exception as e:
            print(f"[ERROR] Problem reading data: {e}")
            continue

except KeyboardInterrupt:
    print("\n[INFO] Monitor stopped by user.")
    arduino.close()
    mqtt_client.loop_stop()
    mqtt_client.disconnect()
