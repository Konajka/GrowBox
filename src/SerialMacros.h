#ifndef SERIAL_MACROS_H
#define SERIAL_MACROS_H

#define SD_KV(key, value) { \
    Serial.print(key); \
    Serial.println(value); \
} 

#define SD_3KV(key1, value1, key2, value2, key3, value3) { \
    Serial.print(key1); \
    Serial.print(value1); \
    Serial.print(key2); \
    Serial.print(value2); \
    Serial.print(key3); \
    Serial.println(value3); \
}

#define SD_KVU_FLOAT(key, value, units) { \
    Serial.print(key); \
    if (isnan(value)) Serial.print("-"); \
    else Serial.print(value); \
    Serial.println(units); \
} 

#endif