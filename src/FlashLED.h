#ifndef FLASH_LED_H
#define FLASH_LED_H

/**
 * Flashes built-in LED.
 * 
 * @param count Number of flashes.
 * @param up Time when LED lights.
 * @param down Time when LED does not light. 
 */ 
void flashLED(int count = 3, int up = 20, int down = 50);

#endif