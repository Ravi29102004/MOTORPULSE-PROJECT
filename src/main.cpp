#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <DHT.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

// ================= MPU6050 =================
Adafruit_MPU6050 mpu;

// ================= DHT22 =================
#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// ================= PINS =================
#define CURRENT_PIN 34
#define BUZZER_PIN 25

// ================= LIMITS =================
float CURRENT_LIMIT = 3.0;
float TEMP_LIMIT = 40.0;
float VIB_LIMIT = 12.0;


void setup()
{
    Serial.begin(115200);

    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    // I2C
    Wire.begin(21, 22);

    // ================= OLED =================
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED not found");
        while (true)
        {
            delay(1000);
        }
    }

    // ================= MPU6050 =================
    if (!mpu.begin())
    {
        Serial.println("MPU6050 not found");
        while (true)
        {
            delay(1000);
        }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);

    // ================= DHT22 =================
    dht.begin();

    // ================= START SCREEN =================
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);

    display.println("MOTORPULSE");
    display.println("----------------");
    display.println("ESP32 Controller");
    display.println("Starting...");

    display.display();

    delay(1500);
}


void loop()
{
    // =================================================
    // CURRENT SENSOR / POTENTIOMETER
    // =================================================

    int raw = analogRead(CURRENT_PIN);

    float current = (raw / 4095.0) * 5.0;


    // =================================================
    // MPU6050 VIBRATION
    // =================================================

    sensors_event_t a;
    sensors_event_t g;
    sensors_event_t temp;

    mpu.getEvent(&a, &g, &temp);

    float vibration = sqrt(
        a.acceleration.x * a.acceleration.x +
        a.acceleration.y * a.acceleration.y +
        a.acceleration.z * a.acceleration.z
    );


    // =================================================
    // TEMPERATURE
    // =================================================

    float temperature = dht.readTemperature();

    if (isnan(temperature))
    {
        temperature = 0;
    }


    // =================================================
    // MOTOR HEALTH / ALARM
    // =================================================

    bool alarm = false;

    if (
        current > CURRENT_LIMIT ||
        temperature > TEMP_LIMIT ||
        vibration > VIB_LIMIT
    )
    {
        alarm = true;

        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
    }


    // =================================================
    // SERIAL MONITOR
    // =================================================

    Serial.print("Current: ");
    Serial.print(current, 2);
    Serial.print(" A");

    Serial.print(" | Vibration: ");
    Serial.print(vibration, 2);

    Serial.print(" | Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" C");

    Serial.print(" | Alarm: ");

    if (alarm)
    {
        Serial.println("ON");
    }
    else
    {
        Serial.println("OFF");
    }


    // =================================================
    // OLED
    // =================================================

    display.clearDisplay();

    display.setCursor(0, 0);

    display.println("MOTORPULSE");
    display.println("----------------");

    display.print("Current : ");
    display.print(current, 2);
    display.println(" A");

    display.print("Vib     : ");
    display.println(vibration, 2);

    display.print("Temp    : ");
    display.print(temperature, 1);
    display.println(" C");

    display.println("----------------");

    if (alarm)
    {
        display.println("STATUS: ALERT!");
    }
    else
    {
        display.println("STATUS: NORMAL");
    }

    display.display();

    delay(500);
}
