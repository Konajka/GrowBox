/**
 * Mackometr
 *
 * Arduino variometer project for crazy paraglider called Macek
 *
 * @author Tomáš Borek, https://github.com/Konajka
 */

#include <Arduino.h>

#define encoderPinA    2
#define encoderPinB    3
#define encoderButton  4
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile int encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile int oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0;

void PinA(){
    cli(); //stop interrupts happening before we read pin values
    reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
    if(reading == B00001100 && aFlag) {//check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
        if (encoderPos > -20) {
            encoderPos --; //decrement the encoder's position count
        }
        bFlag = 0; //reset flags for the next turn
        aFlag = 0; //reset flags for the next turn
    }
    else if (reading == B00000100) {
        bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
    }
    sei(); //restart interrupts
}

void PinB(){
    cli(); //stop interrupts happening before we read pin values
    reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
    if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
        if (encoderPos < 20) {
            encoderPos ++; //increment the encoder's position count
        }
        bFlag = 0; //reset flags for the next turn
        aFlag = 0; //reset flags for the next turn
    }
    else if (reading == B00001000) {
        aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
    }
    sei(); //restart interrupts
}

void initEncoder()
{
    pinMode(encoderPinA,   INPUT_PULLUP);
    pinMode(encoderPinB,   INPUT_PULLUP);
    attachInterrupt(0, PinA, RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
    attachInterrupt(1, PinB, RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
}

void setup() {
    Serial.begin(115200);
    initEncoder();
}

void printPos(int pos) {
    Serial.print("[");
    for (int i = -20; i < pos; i++) Serial.print("-");
    Serial.print("o");
    for (int i = pos + 1; i <= 20; i++) Serial.print("-");
    Serial.print("] (");
    Serial.print(pos);
    Serial.println(")");
}

void loop() {
    if (encoderPos != oldEncPos) {
        oldEncPos = encoderPos;
        int pos = encoderPos;
        printPos(pos < -20 ? -20 : (pos > 20 ? 20 : pos));
    }
}
