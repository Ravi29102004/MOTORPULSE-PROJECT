# MOTORPULSE ⚙️

### Retrofittable Industrial Edge-IoT Smart Automation & Machine Health Monitoring Controller

**Team Name - Spark Innovators**

> **“Make the existing motor intelligent.”**
> **“Every motor has a fingerprint. MOTORPULSE learns it.”**

---

## 📌 Project Overview

**MOTORPULSE** is a retrofittable Industrial Edge-IoT smart automation and machine health monitoring controller designed to monitor the health of existing industrial induction motors without requiring major modifications to the existing motor infrastructure.

The system continuously monitors:

* ⚡ Motor Current
* 🌡️ Motor Temperature
* 📳 Motor Vibration

The collected sensor data is processed at the **edge using an ESP32 controller**. MOTORPULSE identifies abnormal operating conditions and classifies the machine condition into **three severity levels**:

```text
NORMAL → WARNING → CRITICAL
```

Based on the severity, the system provides an appropriate response such as:

```text
NORMAL    → Continue Operation
WARNING   → Inspect / De-load
CRITICAL  → Safe Stop
```

---

# 🎯 Problem Statement

Industrial motors are critical components of manufacturing and automation systems. Unexpected motor failures can lead to:

* Production downtime
* Equipment damage
* Maintenance costs
* Safety risks
* Energy/resource wastage

Traditional monitoring systems can be expensive and may require replacement or modification of existing industrial equipment.

MOTORPULSE aims to provide a **retrofittable and intelligent monitoring solution** that can be attached to existing motors and continuously monitor their operating condition.

---

# 💡 Proposed Solution

MOTORPULSE uses multiple sensors connected to an ESP32-based edge controller.

### Sensor Layer

```text
Current Sensor
      │
      ├──────────────┐
      │              │
MPU6050           DHT22
Vibration        Temperature
      │              │
      └──────┬───────┘
             ↓
           ESP32
             ↓
      Edge Processing
             ↓
      Severity Detection
```

The system processes sensor readings locally and determines the current health state of the motor.

---

# 🔧 Hardware Components

| Component                                 | Purpose                             |
| ----------------------------------------- | ----------------------------------- |
| ESP32                                     | Main edge controller                |
| MPU6050                                   | Vibration / acceleration monitoring |
| DHT22                                     | Temperature monitoring              |
| Current Sensor / Potentiometer Simulation | Motor current monitoring            |
| SSD1306 OLED                              | Local monitoring display            |
| Buzzer                                    | Audible fault indication            |
| Wi-Fi                                     | Future IoT/cloud connectivity       |

---

# 🖥️ Software & Technologies

* C++
* Arduino Framework
* ESP32
* PlatformIO
* Wokwi
* Arduino Wire / I2C
* Adafruit SSD1306
* Adafruit GFX
* Adafruit MPU6050
* DHT Sensor Library
* Git & GitHub

### Planned Backend

* Java
* Spring Boot
* REST API
* JPA / Hibernate
* PostgreSQL / MySQL

---

# 📊 Real-Time Parameters

MOTORPULSE currently monitors three major parameters.

### 1. Current

Current indicates the electrical load of the motor.

```text
Normal       < 3 A
Warning      3 A – 4 A
Critical     > 4 A
```

### 2. Temperature

Temperature helps identify excessive heating.

```text
Normal       < 40°C
Warning      40°C – 50°C
Critical     > 50°C
```

### 3. Vibration

MPU6050 measures acceleration and provides a vibration-related magnitude.

```text
Normal       < 12 m/s²
Warning      12 – 15 m/s²
Critical     > 15 m/s²
```

> These thresholds are currently configured for the prototype/simulation and can be calibrated according to the characteristics of a real industrial motor.

---

# 🚨 Three-Level Severity System

MOTORPULSE now uses a **three-level severity classification** instead of a simple ON/OFF alarm.

## 🟢 Level 1 — NORMAL

The monitored parameters remain within their safe operating range.

```text
Severity: NORMAL
Action: Continue Operation
Buzzer: OFF
```

OLED example:

```text
LEVEL: NORMAL
ACT: NORMAL
```

---

## 🟡 Level 2 — WARNING

One or more parameters have crossed the warning threshold but have not reached the critical threshold.

```text
Severity: WARNING
Action: INSPECT / DE-LOAD
Buzzer: Warning indication
```

Example:

```text
Current: 3.20 A
Temperature: 44.3 C
Vibration: 9.37 m/s²

Severity: WARNING
Action: INSPECT
```

The operator can inspect the motor and take preventive action before the condition becomes critical.

---

## 🔴 Level 3 — CRITICAL

One or more parameters have reached a critical threshold.

```text
Severity: CRITICAL
Action: SAFE STOP
Buzzer: Continuous alarm
```

Example:

```text
Current: 4.50 A
Temperature: 55.0 C
Vibration: 16.20 m/s²

Severity: CRITICAL
Action: SAFE STOP
```

The system can trigger a local alarm and, in a future industrial implementation, initiate a controlled shutdown/de-load mechanism.

---

# 🔔 Alarm & Buzzer Logic

The prototype uses the following response:

```text
                 SENSOR DATA
                      │
                      ↓
              Severity Analysis
                      │
          ┌───────────┼───────────┐
          ↓           ↓           ↓
       NORMAL       WARNING     CRITICAL
          │           │           │
          ↓           ↓           ↓
       No Alarm     Inspect     Safe Stop
                      │           │
                      ↓           ↓
                   Warning      Buzzer
                               / Alarm
```

The buzzer is activated for critical conditions using the ESP32 buzzer output.

---

# 📺 OLED Monitoring

The SSD1306 OLED provides local real-time information.

Example:

```text
MOTORPULSE
----------------
Current : 1.49 A
Vib     : 9.37
Temp    : 44.3 C
----------------
LEVEL: WARNING
ACT: INSPECT
```

For a critical condition:

```text
MOTORPULSE
----------------
Current : 4.50 A
Vib     : 16.20
Temp    : 55.0 C
----------------
LEVEL: CRITICAL
ACT: SAFE STOP
```

---

# 💻 Serial Monitoring

The ESP32 also sends real-time sensor information through the Serial Monitor.

Example:

```text
Current: 1.49 A | Vibration: 9.37 m/s2 | Temperature: 44.3 C | Severity: WARNING | Action: INSPECT
```

Critical example:

```text
Current: 4.50 A | Vibration: 16.20 m/s2 | Temperature: 55.0 C | Severity: CRITICAL | Action: SAFE STOP
```

---

# 🧪 Wokwi Simulation

The current prototype is simulated using **Wokwi**.

The simulation includes:

```text
ESP32
 │
 ├── MPU6050
 │
 ├── DHT22
 │
 ├── Potentiometer
 │
 ├── SSD1306 OLED
 │
 └── Buzzer
```

### Simulation Features

* Real-time current simulation
* Temperature simulation
* Vibration/acceleration simulation
* OLED monitoring
* Severity detection
* Buzzer alarm
* Serial monitoring

---

# 🏗️ System Architecture

```text
              INDUSTRIAL MOTOR
                     │
          ┌──────────┼──────────┐
          ↓          ↓          ↓
       Current    Vibration  Temperature
        Sensor      MPU6050      DHT22
          │          │          │
          └──────────┼──────────┘
                     ↓
                  ESP32
                     │
             Edge Processing
                     │
             Severity Analysis
                     │
        ┌────────────┼────────────┐
        ↓            ↓            ↓
      NORMAL       WARNING     CRITICAL
        │            │            │
        ↓            ↓            ↓
   Operation      Inspect      Safe Stop
                     │
                     ↓
              OLED + Buzzer
```

---

# 🌐 Future IoT Architecture

The next stage of MOTORPULSE is to connect the ESP32 to a backend server.

```text
ESP32
  │
  │ Wi-Fi
  ↓
Spring Boot REST API
  │
  ↓
Service Layer
  │
  ↓
JPA / Hibernate
  │
  ↓
PostgreSQL / MySQL
  │
  ↓
MOTORPULSE Dashboard
```

The backend will store:

* Machine information
* Sensor readings
* Severity events
* Alert history
* Maintenance records
* Machine health history

---

# 🤖 Future Edge AI

The current prototype uses threshold-based severity detection.

Future versions will introduce **Edge AI / TinyML**.

```text
Sensor Data
     ↓
Feature Extraction
     ↓
Motor Fingerprint
     ↓
TinyML / Edge AI
     ↓
Anomaly Detection
     ↓
NORMAL / WARNING / CRITICAL
```

The objective is to learn the normal operating fingerprint of each motor and detect deviations from its normal behavior.

---

# 🔮 Future Enhancements

* [ ] Spring Boot backend
* [ ] REST API
* [ ] PostgreSQL/MySQL integration
* [ ] JPA/Hibernate
* [ ] React dashboard
* [ ] Real-time machine dashboard
* [ ] Historical sensor graphs
* [ ] Alert history
* [ ] Maintenance management
* [ ] MQTT communication
* [ ] TinyML / Edge AI
* [ ] Motor-specific health fingerprint
* [ ] Predictive maintenance
* [ ] Industrial-grade sensors
* [ ] Automatic de-loading
* [ ] Safe shutdown mechanism
* [ ] Cloud deployment
* [ ] Multi-machine monitoring

---

# ⚠️ Current Limitations

1. The current prototype is primarily a simulation/prototype implementation.
2. The current thresholds are fixed and need calibration for real industrial motors.
3. MPU6050 is being used as a prototype vibration sensor; industrial-grade vibration sensors would provide more reliable measurements.
4. Current sensing is currently simulated using a potentiometer in Wokwi.
5. Edge AI/TinyML is planned for future development.
6. The current prototype does not directly control an industrial motor.
7. Industrial electrical isolation and protection mechanisms are required before real-world deployment.
8. Backend/cloud connectivity is part of the planned next stage.

---

# 📁 Project Structure

```text
MOTORPULSE/
│
├── src/
│   └── main.cpp
│
├── diagram.json
├── platformio.ini
├── README.md
│
└── .gitignore
```

---

# 🚀 Current Development Status

### Completed ✅

* ESP32 controller setup
* PlatformIO project
* Wokwi simulation
* MPU6050 integration
* DHT22 integration
* Current simulation
* SSD1306 OLED integration
* Serial monitoring
* Real-time sensor monitoring
* Fault detection
* Three-level severity classification
* NORMAL / WARNING / CRITICAL states
* Action classification
* Buzzer alarm
* GitHub project setup

### Currently Planned 🔄

* Spring Boot backend
* REST API
* Database integration
* IoT data transmission
* Web dashboard
* Edge AI / TinyML
* Predictive maintenance

---

# 👥 Team

**Team Name - Spark Innovators**

### Project

**MOTORPULSE**

### Theme

**Smart Resource Conservation**

### Category

**Hardware / Industrial IoT**

---

# 🏁 Vision

MOTORPULSE aims to transform existing industrial motors into **intelligent, connected and condition-aware machines** without requiring complete replacement of the existing infrastructure.

> **Make the existing motor intelligent.**

> **Every motor has a fingerprint. MOTORPULSE learns it.**




**********************************************=========================***********************
Normal Condition


<img width="1280" height="948" alt="image" src="https://github.com/user-attachments/assets/0060d4d5-bb78-4acf-a8f4-151e26f4d3a7" />





Alert Condition




<img width="1280" height="948" alt="image" src="https://github.com/user-attachments/assets/81c1159e-7e95-47a6-aa4f-feeacd1834db" />


