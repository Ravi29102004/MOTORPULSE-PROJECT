# MOTORPULSE ⚡

### Retrofittable Industrial Edge-IoT Smart Automation & Machine Health Monitoring Controller

> **Make the existing motor intelligent.**
> *Every motor has a fingerprint. MOTORPULSE learns it.*

**Team Name:** Spark Innovators

---

## 📌 Overview

**MOTORPULSE** is a retrofit-first Industrial IoT and Edge AI controller designed to monitor the health of existing industrial induction motors without replacing the existing motor or machine infrastructure.

The system collects important motor parameters such as:

* ⚡ Current
* 🌡️ Temperature
* 📳 Vibration / Acceleration

An **ESP32-based edge controller** processes the sensor data locally and identifies abnormal operating conditions.

The system can generate alerts based on predefined thresholds and can later be extended with an Edge AI model for motor-specific anomaly detection.

---

## 🎯 Objective

The main objective of MOTORPULSE is to provide an affordable intelligence layer for existing industrial motors.

Instead of replacing conventional motors with expensive smart motors, MOTORPULSE can be retrofitted onto existing equipment to provide:

```text
Existing Motor
      ↓
Sensors
      ↓
ESP32 Edge Controller
      ↓
Data Processing
      ↓
Motor Health Analysis
      ↓
NORMAL / ALERT
      ↓
Local Alert / Future Cloud or Server
```

---

## 🔧 Current Prototype

The current prototype is developed using:

| Component        | Purpose                          |
| ---------------- | -------------------------------- |
| ESP32 Dev Module | Edge controller                  |
| MPU6050          | Vibration / acceleration sensing |
| DHT22            | Temperature sensing              |
| Potentiometer    | Simulated current sensor         |
| OLED SSD1306     | Local monitoring display         |
| Buzzer           | Fault / alert indication         |

---

## 🧠 Monitoring Parameters

### 1. Current Monitoring

The prototype currently uses a potentiometer to simulate motor current.

```text
Current > 3 A
       ↓
     ALERT
       ↓
    BUZZER
```

For a real industrial deployment, the potentiometer can be replaced by an appropriate **isolated current sensor / split-core CT sensor**.

### 2. Temperature Monitoring

The DHT22 provides temperature data.

Current prototype threshold:

```text
Temperature > 40°C
        ↓
      ALERT
```

### 3. Vibration / Acceleration Monitoring

The MPU6050 measures acceleration along the X, Y and Z axes.

The prototype calculates the acceleration magnitude to obtain a basic vibration indicator.

```text
Acceleration
      ↓
X + Y + Z measurements
      ↓
Magnitude calculation
      ↓
Threshold comparison
      ↓
ALERT
```

Current prototype threshold:

```text
Vibration > 12 m/s²
        ↓
      ALERT
```

---

## 🚨 Alert System

If any monitored parameter crosses its configured threshold:

```text
Current > Limit
      OR
Temperature > Limit
      OR
Vibration > Limit
      ↓
    ALARM ON
      ↓
    BUZZER ON
```

The OLED displays:

```text
STATUS: ALERT!
```

Otherwise:

```text
STATUS: NORMAL
```

---

## 🖥️ OLED Display

The OLED provides real-time local information:

```text
MOTORPULSE
----------------
Current : 2.15 A
Vib     : 9.84
Temp    : 25.0 C
----------------
STATUS: NORMAL
```

---

## 🧪 Simulation

The prototype is being developed and tested using **Wokwi**.

Simulation components include:

* ESP32
* OLED SSD1306
* MPU6050
* DHT22
* Potentiometer
* Buzzer

---

## 🛠️ Software & Development Tools

* C++
* Arduino Framework
* PlatformIO
* VS Code
* Wokwi
* Git
* GitHub

---

## 📁 Project Structure

```text
MOTORPULSE/
│
├── include/
├── lib/
├── src/
│   └── main.cpp
├── test/
│
├── diagram.json
├── platformio.ini
├── wokwi.toml
├── .gitignore
└── README.md
```

---

## ⚙️ PlatformIO Configuration

```text
Board: ESP32 Dev Module
Framework: Arduino
Platform: Espressif 32
```

Build:

```bash
pio run
```

---

## ▶️ Running the Simulation

### 1. Build the firmware

```bash
pio run
```

### 2. Start Wokwi

In VS Code:

```text
Command Palette
→ Wokwi: Start Simulator
```

### 3. Serial Monitor

```text
115200 baud
```

Example:

```text
Current: 1.25 A | Vibration: 9.82 | Temperature: 25.0 C | Alarm: OFF
```

---

## 🔌 Pin Configuration

| Device                         | ESP32 Pin |
| ------------------------------ | --------- |
| OLED SDA                       | GPIO 21   |
| OLED SCL                       | GPIO 22   |
| MPU6050 SDA                    | GPIO 21   |
| MPU6050 SCL                    | GPIO 22   |
| DHT22 DATA                     | GPIO 15   |
| Current Sensor / Potentiometer | GPIO 34   |
| Buzzer                         | GPIO 25   |

OLED and MPU6050 share the same I²C bus.

---

## 🔮 Future Development

* [ ] Real split-core CT current sensor
* [ ] Real industrial vibration sensor
* [ ] Improved temperature sensing
* [ ] Motor-specific baseline learning
* [ ] Edge AI anomaly detection
* [ ] Motor health score
* [ ] Fault classification
* [ ] Severity levels
* [ ] Inspect / De-load / Safe Stop recommendations
* [ ] Local server integration
* [ ] MQTT communication
* [ ] Web dashboard
* [ ] Historical sensor data
* [ ] Predictive maintenance
* [ ] Cloud integration

---

## 🧠 Edge AI Vision

The long-term goal is to move from simple threshold-based monitoring toward a motor-specific health model.

```text
Sensor Data
     ↓
Current + Vibration + Temperature
     ↓
Feature Extraction
     ↓
Motor Fingerprint
     ↓
Edge AI Model
     ↓
Anomaly Detection
     ↓
Severity
     ↓
Action
```

Possible output:

```text
NORMAL
   ↓
INSPECT
   ↓
DE-LOAD
   ↓
SAFE STOP
```

---

## 🌐 Local Server Integration

MOTORPULSE can be extended so that the ESP32 performs local processing while sending selected sensor data to a local server.

```text
Industrial Motor
       ↓
     Sensors
       ↓
      ESP32
   Edge Processing
       ↓
   Local Network
       ↓
   Local Server
       ↓
   Database
       ↓
   Dashboard
```

---

## ⚠️ Safety Note

The current Wokwi prototype is a simulation and development model.

For real industrial motors, **never connect motor mains voltage directly to the ESP32 or prototype electronics**.

Real deployment requires appropriate:

* Electrical isolation
* Current sensing
* Protection circuits
* Industrial-rated sensors
* Power supply
* Enclosure
* Grounding
* Overcurrent protection
* Emergency-stop mechanisms

---

## 📌 Project Status

**Current Stage:** Prototype / Simulation

```text
✅ Current monitoring simulation
✅ Temperature monitoring
✅ Acceleration monitoring
✅ OLED display
✅ Threshold-based alarm
✅ Buzzer alert
✅ Serial monitoring
✅ Wokwi simulation
```

The next major development step is **real sensor integration followed by Edge AI-based motor anomaly detection**.

---

## 👥 Team

**Team Name:** Spark Innovators

**Project:** MOTORPULSE

**Concept:** Retrofittable Industrial Edge-IoT Motor Health Monitoring

> **Make the existing motor intelligent.**




**********************************************=========================***********************
Normal Condition


<img width="1280" height="948" alt="image" src="https://github.com/user-attachments/assets/0060d4d5-bb78-4acf-a8f4-151e26f4d3a7" />





Alert Condition




<img width="1280" height="948" alt="image" src="https://github.com/user-attachments/assets/81c1159e-7e95-47a6-aa4f-feeacd1834db" />


