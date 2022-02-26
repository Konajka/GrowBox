#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define GROWBOX_VERSION "0.1"

// Temperature and humidity sensor
#define COMPONENT_TEMPERATURE_HUMIDITY "DHT22"
#define DHT_TYPE DHT22
DHT_Unified temperatureHumiditySensor(D5, DHT_TYPE);

/**
 * Flashes built-in LED.
 * 
 * @param count Number of flashes.
 * @param up Time when LED lights.
 * @param down Time when LED does not light. 
 */ 
void flash(int count = 3, int up = 20, int down = 50) {
    for (int i = 0; i < count; i++) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(up);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(down);
    }
}

// TODO serialDump(caption, value, units)
/**
 * Prints double value information string to serial line.
 * 
 * @param caption Value caption.
 * @param value The value.
 * @param precision Number of fractional digits.
 * @param units Value units.
 */ 
void serialDump(const __FlashStringHelper *caption, const double value, const int precision, const __FlashStringHelper *units)
{
    Serial.print(caption);
    if (isnan(value)) 
        Serial.print("-");    
     else 
        Serial.print(value, precision);   
    Serial.println(units);
}

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
    Serial.print(F("Temperature sensor ")); 
    Serial.print(sensor.name);
    Serial.print(F(", driver ")); 
    Serial.print(sensor.version);
//   Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
//   Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
//   Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
//   Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println();

    // Humidity sensor info
    // TODO Humidity sensor info
    
    // Read initial values
    sensors_event_t event;
    temperatureHumiditySensor.temperature().getEvent(&event);
    float temperature = event.temperature;
    temperatureHumiditySensor.humidity().getEvent(&event);
    float humidity = event.relative_humidity;

    serialDump(F("Initial temperature "), temperature, 1, F(" °C"));
    serialDump(F("Initial humidity "), humidity, 0, F(" %"));
#endif    
}

/**
 * Setup application.
 */
void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.print(F("GrowBox "));
    Serial.println(F(GROWBOX_VERSION));

    // Use built-in LED to signalize status
    pinMode(LED_BUILTIN, OUTPUT);
    flash(2, 200, 100);

    // Initialize devices
    setupTemperatureAndHumiditySensor();
    Serial.println(F("GrowBox initialized"));
}

/**
 * Main application loop.
 */
void loop() {
    flash();
    delay(1000);
}