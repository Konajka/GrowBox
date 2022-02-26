#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT.h>
#include <DHT_U.h>
#include <U8g2lib.h>
#include "SerialMacros.h"
#include "FlashLED.h"
#include "Model.h"

#define GROWBOX_VERSION "0.1"

// Temperature and humidity sensor DHT22
#define COMPONENT_TEMPERATURE_HUMIDITY "DHT22"
#define DHT_TYPE DHT22
DHT_Unified temperatureHumiditySensor(D5, DHT_TYPE);

// I2C OLED Display 128x64, driver SSD1106
#define COMPONENT_DISPLAY "SSD1106_128x64"
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// UX data model
GrowBoxDataModel model;

/**
 * Initializes temperature and humidity sensor and prints device info to serial line
 */
void setupTemperatureAndHumiditySensor() {
#ifdef COMPONENT_TEMPERATURE_HUMIDITY

    Serial.println(F("Initializing temperature and humidity sensor"));
    temperatureHumiditySensor.begin();

    // Temperature sensor info
    sensor_t sensor;
    temperatureHumiditySensor.temperature().getSensor(&sensor);
    SD_3KV(F("Temperature sensor = "), sensor.name, F(", version = "), sensor.version, F(", ID = "), sensor.sensor_id);

    // Humidity sensor info
    temperatureHumiditySensor.humidity().getSensor(&sensor);
    SD_3KV(F("Humidity sensor = "), sensor.name, F(", version = "), sensor.version, F(", ID = "), sensor.sensor_id);

#endif
}

void updateTemperatureAndHumidity(GrowBoxDataModel &model) {
#ifdef COMPONENT_TEMPERATURE_HUMIDITY

    sensors_event_t event;
    temperatureHumiditySensor.temperature().getEvent(&event);
    model.temperature = event.temperature;
    SD_KVU_FLOAT(F("Temp = "), event.temperature, F(" °C"));

    temperatureHumiditySensor.humidity().getEvent(&event);
    model.humidity = event.relative_humidity;
    SD_KVU_FLOAT(F("Hum = "), event.relative_humidity, F(" %"));

#endif
}

/**
 * Initializes U8G2 library
 */
void setupDisplay() {
#ifdef COMPONENT_DISPLAY

    Serial.println(F("Initializing display"));
    u8g2.begin();

#endif
}

void updateDisplay(GrowBoxDataModel model) {
#ifdef COMPONENT_DISPLAY

    char buffer[10];

    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_6x10_mr);
        u8g2.drawStr(0, 12, "GrowBox");

        sprintf(buffer, "T %.1f °C", model.temperature);
        u8g2.drawStr(0, 24, buffer);

        sprintf(buffer, "H %.0f %%", model.humidity);
        u8g2.drawStr(0, 36, buffer);
    } while (u8g2.nextPage());

#endif
}

/**
 * Setup application.
 */
void setup() {
    Serial.begin(9600);
    Serial.println();
    SD_KV(F("GrowBox "), F(GROWBOX_VERSION));

    // Use built-in LED to signalize status
    pinMode(LED_BUILTIN, OUTPUT);
    flashLED(2, 200, 100);

    // Initialize devices
    setupTemperatureAndHumiditySensor();
    setupDisplay();
    Serial.println(F("GrowBox initialized"));
}

/**
 * Main application loop.
 */
void loop() {
    flashLED();
    updateTemperatureAndHumidity(model);
    updateDisplay(model);
    delay(2000);
}