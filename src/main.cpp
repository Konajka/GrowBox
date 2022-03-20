// GrowBox
#include <Arduino.h>

void flash(int speed = 50, int count = 4) {
    for (int i = 0; i < count; i++) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(speed);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(speed);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    delay(1000);
    Serial.println("Hello World!");

    flash(40, 2);
}
