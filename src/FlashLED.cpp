#include <Arduino.h>
#include "FlashLED.h"

void flashLED(int count, int up, int down) {
    for (int i = 0; i < count; i++) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(up);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(down);
    }
}