#include <Arduino.h>


// Pins
int inputPin = 32;
int outputPin = 14;

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
unsigned long millsElapsed;
int timesMillsElapsed;
int yolo = 0;
int yolo2;


void setup(){
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    Serial.begin(115200);
}

void timing(){
    mills = millis();

    if (mills < 1000) {
        millsInContext = mills;
    } else {
        millsInContext = mills % 1000;
    }

    totalSecs = mills / 1000;

    if (totalSecs > 0 && totalSecs < 60){
        secs = totalSecs;
    } else if (totalSecs >= 60 && totalSecs < 3600){
        secs = totalSecs % 60;
        mins = totalSecs / 60;
    } else {
        secs = totalSecs % 60;
        totalMins = totalSecs / 60;
        mins = totalMins % 60;
        hours = totalSecs / 3600;
    }
    
}

void makeSig(){
    millsElapsed = mills / 500;

    timesMillsElapsed = millsElapsed % 2;

    if (timesMillsElapsed == 0) {
        digitalWrite(outputPin, HIGH);
    } else {
        digitalWrite(outputPin, LOW);
    }

}

void capture(){
    before = current;

    readings = digitalRead(inputPin);

    if (readings == 0) {
        current = 1;
    } else {
        current = 0;
    }

    if (current == before) {
        nothing = 0;
    } else {
        yolo++;
        Serial.printf("%d,%d,%02d:%02d:%02d:%04lu\n", inputPin, readings, hours, mins, secs, millsInContext);
    }
}

void loop(){
    if (yolo <= 20){
        timing();
        makeSig();
        capture();
    } else {
        nothing = 0;
    }
    
}

