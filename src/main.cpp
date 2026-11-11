#include <Arduino.h>


// Pins
int inputPin = 33;

// Variables
int readings;
int before = 0;
int current = 0;
int nothing;
unsigned long mills; 
int secs; 
int totalSecs; 
int mins; 
int hours; 
int totalMins;
unsigned long millsInContext;

void setup(){
    pinMode(inputPin, INPUT_PULLUP);
    Serial.begin(115200);
}

void timing(){
    mills = millis();

    if (mills < 1000) {
        millsInContext = mills;
    } else if (mills >= 1000){
        millsInContext = mills % 1000;
    }

    totalSecs = mills / 1000;

    if (totalSecs > 0 && totalSecs < 60){
        secs = totalSecs;
    } else if (totalSecs >= 60 && totalSecs < 3600){
        secs = totalSecs % 60;
        mins = totalSecs / 60;
    } else if (totalSecs >= 3600){
        secs = totalSecs % 60;
        totalMins = totalSecs / 60;
        mins = totalMins % 60;
        hours = totalSecs / 3600;
    }


    
    
}

void loop(){
    before = current;

    readings = digitalRead(inputPin);

    timing();

    if (readings == 0) {
        current = 1;
    } else {
        current = 0;
    }

    if (current == before) {
        nothing = 0;
    } else {
        Serial.printf("%d,%d,%02d:%02d:%02d:%04lu\n", inputPin, readings, hours, mins, secs, millsInContext);
    }
}

