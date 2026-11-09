#include <Arduino.h>

// Pins
int buttonPin = 33;
int ledPin = 21;

// Variables
int readings;
int before = 0;
int current = 0;
int realTing = 0;

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    before = current;

    readings = digitalRead(buttonPin);

    if (readings == 0) {
        current = 1;
    } else {
        current = 0;
    }

    if (current == before) {
        realTing = 0;
    } else {
        Serial.printf("diff\n");
    }
    
    delay(250);
}
