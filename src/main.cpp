#include <Arduino.h>


// Pins
int inputPin = 32;
int outputPin = 14;

// Variables
int readings;
int before;
int current;
unsigned long mills; 
int secs; 
int totalSecs; 
int mins; 
int hours; 
int totalMins;
unsigned long microsInContext;
unsigned long microsElapsed;
int timesMicrosElapsed;
int yolo = 0;
int yolo2;
unsigned long timeHappened[20];
int levelItsAt[20];
unsigned long betweenEvents[20];
int printed = 0;
unsigned long micro;
bool initialReadIf = false;
int initRead;

void setup(){
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    Serial.begin(115200);
}

void timing(){

    mills = millis();

    if (micro < 1000000) {
        microsInContext = micro;
    } else {
        microsInContext = micro % 1000000;
    }

    totalSecs = micro / 1000000;

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
    microsElapsed = micro / 500000;

    timesMicrosElapsed = microsElapsed % 2;

    if (timesMicrosElapsed == 0) {
        digitalWrite(outputPin, HIGH);
    } else {
        digitalWrite(outputPin, LOW);
    }

}

void capture()
    before = current;
    readings = digitalRead(inputPin);

    if (initialReadIf == false){
        initRead = readings;
        before = readings;
        current = readings;
        initialReadIf = true;
    }

    current = readings;

    if (current != before) {
        micro = micros();
        levelItsAt[yolo] = readings;
        timeHappened[yolo] = micro;
        yolo++;
        //Serial.printf("%d,%d,%02d:%02d:%02d:%04lu\n", inputPin, readings, hours, mins, secs, millsInContext);
    } 
}

void loop(){

    if (yolo < 20){
        makeSig();
        capture();
    }

    if(yolo == 20 && printed == 0){
        Serial.printf("Initial reading: %d \n", initRead);
        Serial.printf("reading: %d, time(micros): %lu \n", levelItsAt[0], timeHappened[0]);

        for(int c = 1; c < 20; c++) {
            betweenEvents[c] = timeHappened[c] - timeHappened[c - 1];
            Serial.printf("reading: %d, time(micros): %lu Time between last event:%lu \n", levelItsAt[c], timeHappened[c], betweenEvents[c]);
        }

        printed = 1;
    }
}

