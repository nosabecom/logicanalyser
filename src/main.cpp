#include <Arduino.h>


// Pins
int buttonPin = 33;
int ledPin = 21;

// Variables
int readings;
int before = 0;
int current = 0;
int realTing = 0;
int secs; 
unsigned long mills;
int totalSecs;
int mins;
int hours;
int totalMins;

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void timing(){
    mills = millis();

    totalSecs = mills / 1000;

    if (totalSecs > 0 && totalSecs < 60){
        secs = totalSecs;
    } else if (totalSecs > 60 && totalSecs < 3600){
        secs = totalSecs % 60;
        mins = totalSecs / 60;
    } else if (totalSecs > 3600){
        secs = totalSecs % 60;
        totalMins = totalSecs / 60;
        mins = totalMins % 60;
        hours = totalSecs / 3600;
    }

    
    
}

void loop(){
    before = current;

    readings = digitalRead(buttonPin);

    timing();

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
        
    }
   timed();
   Serial.printf("Time: %d:%d:%d\n", hours, mins, secs);
   delay(1000);
}

