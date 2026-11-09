#include <Arduino.h>

// Pins
int buttonPin = 33;

// Variables
int readings;

void setup(){
    pinMode(buttonPin, INPUT_PULLDOWN);
    Serial.begin(115200);
}

void loop(){
    Serial.print(buttonPin);
}
