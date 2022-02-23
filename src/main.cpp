#include <Arduino.h>

#define GROWBOX_VERSION "0.1"

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

/**
 * Setup application.
 */
void setup() {
    Serial.begin(9600);
    Serial.print(F("GrowBox "));
    Serial.println(F(GROWBOX_VERSION));

    // Use built-in LED to signalize status
    pinMode(LED_BUILTIN, OUTPUT);
    flash(2, 200, 100);

    Serial.println(F("GrowBox initialized"));
}

/**
 * Main application loop.
 */
void loop() {
    flash();
    delay(1000);
}