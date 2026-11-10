#include <Arduino.h>

// Pins
int buttonPin = 33;
int ledPin = 21;

// Variables
int readings;
int before = 0;
int current = 0;
int realTing = 0;
unsigned long timing = 0;

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    before = current;

    readings = digitalRead(buttonPin);

    timing = micros();

    if (readings == 0) {
        current = 1;
        digitalWrite(ledPin, HIGH);
    } else {
        current = 0;
        digitalWrite(ledPin, LOW);
    }

    if (current == before) {
        realTing = 0;
    } else {
        Serial.printf("Time: %lu\n", timing);
    }
    
    delay(150);
}
