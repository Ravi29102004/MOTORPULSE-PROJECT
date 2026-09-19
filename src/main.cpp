#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <DHT.h>

// ======================================================
// MOTORPULSE
// Team: Spark Innovators
// 3-Level Severity Monitoring
// ======================================================

// ================= OLED =================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1);

// ================= MPU6050 =================

Adafruit_MPU6050 mpu;

// ================= DHT22 =================

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// ================= INPUTS =================

#define CURRENT_PIN 34
#define BUZZER_PIN 25

// ======================================================
// LIMITS
// ======================================================

// Current
const float CURRENT_WARNING = 3.0;
const float CURRENT_CRITICAL = 4.0;

// Temperature
const float TEMP_WARNING = 40.0;
const float TEMP_CRITICAL = 50.0;

// Vibration
const float VIB_WARNING = 12.0;
const float VIB_CRITICAL = 15.0;

// ======================================================
// SENSOR VARIABLES
// ======================================================

float current = 0.0;
float vibration = 0.0;
float temperature = 24.0;

// ======================================================
// FAULT STATES
// ======================================================

bool currentWarning = false;
bool currentCritical = false;

bool temperatureWarning = false;
bool temperatureCritical = false;

bool vibrationWarning = false;
bool vibrationCritical = false;

// ======================================================
// SEVERITY
// ======================================================

enum Severity
{
  NORMAL,
  WARNING,
  CRITICAL
};

Severity systemSeverity = NORMAL;

// ======================================================
// DHT TIMER
// ======================================================

unsigned long lastDHTRead = 0;

const unsigned long DHT_INTERVAL = 2000;

// ======================================================
// SETUP
// ======================================================

void setup()
{

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("       MOTORPULSE STARTING");
  Serial.println("================================");

  Serial.println("Serial communication OK");

  // ---------------- BUZZER ----------------

  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  // ---------------- I2C ----------------

  Wire.begin(SDA_PIN, SCL_PIN);

  // ---------------- OLED ----------------

  if (!display.begin(
          SSD1306_SWITCHCAPVCC,
          0x3C))
  {

    Serial.println("OLED ERROR");

    while (true)
    {
      delay(1000);
    }
  }

  Serial.println("OLED: OK");

  // ---------------- MPU6050 ----------------

  if (!mpu.begin(0x68, &Wire))
  {

    Serial.println("MPU6050 ERROR");

    while (true)
    {
      delay(1000);
    }
  }

  Serial.println("MPU6050: OK");

  mpu.setAccelerometerRange(
      MPU6050_RANGE_4_G);

  mpu.setGyroRange(
      MPU6050_RANGE_250_DEG);

  mpu.setFilterBandwidth(
      MPU6050_BAND_21_HZ);

  // ---------------- DHT22 ----------------

  dht.begin();

  Serial.println("DHT22: OK");

  // ---------------- OLED START SCREEN ----------------

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);

  display.println("MOTORPULSE");
  display.println("----------------");
  display.println("ESP32 Controller");
  display.println("Starting...");
  display.println();
  display.println("Sensors OK");

  display.display();

  delay(1500);

  Serial.println("--------------------------------");
  Serial.println("MOTORPULSE READY");
  Serial.println("--------------------------------");
  Serial.println();
}

// ======================================================
// DETERMINE SEVERITY
// ======================================================

void calculateSeverity()
{

  // Reset
  currentWarning = false;
  currentCritical = false;

  temperatureWarning = false;
  temperatureCritical = false;

  vibrationWarning = false;
  vibrationCritical = false;

  // ---------------- CURRENT ----------------

  if (current >= CURRENT_CRITICAL)
  {

    currentCritical = true;
  }
  else if (current >= CURRENT_WARNING)
  {

    currentWarning = true;
  }

  // ---------------- TEMPERATURE ----------------

  if (temperature >= TEMP_CRITICAL)
  {

    temperatureCritical = true;
  }
  else if (temperature >= TEMP_WARNING)
  {

    temperatureWarning = true;
  }

  // ---------------- VIBRATION ----------------

  if (vibration >= VIB_CRITICAL)
  {

    vibrationCritical = true;
  }
  else if (vibration >= VIB_WARNING)
  {

    vibrationWarning = true;
  }

  // ==================================================
  // SYSTEM SEVERITY
  // ==================================================

  if (
      currentCritical ||
      temperatureCritical ||
      vibrationCritical)
  {

    systemSeverity = CRITICAL;
  }
  else if (
      currentWarning ||
      temperatureWarning ||
      vibrationWarning)
  {

    systemSeverity = WARNING;
  }
  else
  {

    systemSeverity = NORMAL;
  }
}

// ======================================================
// GET SEVERITY TEXT
// ======================================================

const char *getSeverityText()
{

  switch (systemSeverity)
  {

  case NORMAL:
    return "NORMAL";

  case WARNING:
    return "WARNING";

  case CRITICAL:
    return "CRITICAL";
  }

  return "UNKNOWN";
}

// ======================================================
// GET ACTION
// ======================================================

const char *getActionText()
{

  switch (systemSeverity)
  {

  case NORMAL:
    return "NORMAL";

  case WARNING:
    return "INSPECT";

  case CRITICAL:
    return "SAFE STOP";
  }

  return "UNKNOWN";
}

// ======================================================
// SERIAL OUTPUT
// ======================================================

void printSerialData()
{

  Serial.print("Current: ");
  Serial.print(current, 2);

  Serial.print(" A | Vibration: ");
  Serial.print(vibration, 2);

  Serial.print(" m/s2 | Temperature: ");
  Serial.print(temperature, 1);

  Serial.print(" C | Severity: ");
  Serial.print(getSeverityText());

  Serial.print(" | Action: ");
  Serial.print(getActionText());

  Serial.print(" | Reason: ");

  bool reasonPrinted = false;

  // Current
  if (currentCritical)
  {

    Serial.print("CURRENT_CRITICAL");
    reasonPrinted = true;
  }
  else if (currentWarning)
  {

    Serial.print("CURRENT_WARNING");
    reasonPrinted = true;
  }

  // Temperature
  if (temperatureCritical)
  {

    if (reasonPrinted)
      Serial.print(", ");

    Serial.print("TEMPERATURE_CRITICAL");

    reasonPrinted = true;
  }
  else if (temperatureWarning)
  {

    if (reasonPrinted)
      Serial.print(", ");

    Serial.print("TEMPERATURE_WARNING");

    reasonPrinted = true;
  }

  // Vibration
  if (vibrationCritical)
  {

    if (reasonPrinted)
      Serial.print(", ");

    Serial.print("VIBRATION_CRITICAL");

    reasonPrinted = true;
  }
  else if (vibrationWarning)
  {

    if (reasonPrinted)
      Serial.print(", ");

    Serial.print("VIBRATION_WARNING");

    reasonPrinted = true;
  }

  if (!reasonPrinted)
  {

    Serial.print("NONE");
  }

  Serial.println();
}

// ======================================================
// OLED OUTPUT
// ======================================================

void updateOLED()
{

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);

  display.println("MOTORPULSE");
  display.println("----------------");

  // Current
  display.print("Current : ");
  display.print(current, 2);
  display.println(" A");

  // Vibration
  display.print("Vib     : ");
  display.print(vibration, 2);
  display.println();

  // Temperature
  display.print("Temp    : ");
  display.print(temperature, 1);
  display.println(" C");

  display.println("----------------");

  // Severity
  display.print("LEVEL: ");
  display.println(getSeverityText());

  // Action
  display.print("ACT: ");
  display.println(getActionText());

  display.display();
}

// ======================================================
// MAIN LOOP
// ======================================================

void loop()
{

  // ==================================================
  // CURRENT
  // ==================================================

  int rawCurrent = analogRead(CURRENT_PIN);

  current =
      (rawCurrent / 4095.0) * 5.0;

  // ==================================================
  // MPU6050
  // ==================================================

  sensors_event_t a;
  sensors_event_t g;
  sensors_event_t mpuTemp;

  mpu.getEvent(
      &a,
      &g,
      &mpuTemp);

  vibration = sqrt(
      a.acceleration.x * a.acceleration.x +
      a.acceleration.y * a.acceleration.y +
      a.acceleration.z * a.acceleration.z);

  // ==================================================
  // DHT22
  // ==================================================

  if (
      lastDHTRead == 0 ||
      millis() - lastDHTRead >= DHT_INTERVAL)
  {

    float newTemperature =
        dht.readTemperature();

    if (!isnan(newTemperature))
    {

      temperature =
          newTemperature;
    }

    lastDHTRead = millis();
  }

  // ==================================================
  // CALCULATE SEVERITY
  // ==================================================

  calculateSeverity();

  // ==================================================
  // BUZZER
  // ==================================================

  if (systemSeverity == CRITICAL)
  {

    digitalWrite(
        BUZZER_PIN,
        HIGH);
  }
  else
  {

    digitalWrite(
        BUZZER_PIN,
        LOW);
  }

  // ==================================================
  // SERIAL
  // ==================================================

  printSerialData();

  // ==================================================
  // OLED
  // ==================================================

  updateOLED();

  // ==================================================
  // LOOP DELAY
  // ==================================================

  delay(500);
}