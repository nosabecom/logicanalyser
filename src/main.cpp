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
bool printed = false;
bool initialReadIf = false;
int initRead;
unsigned long initTime;
const int maxEnv = 1024;
unsigned long betweenEvents;
unsigned long timeHappened[maxEnv];
int levelItsAt[maxEnv];
int tarEnv = 20;
bool thecaptured = false;
const char* reasonStop = "NONE";
unsigned long sTime = 0;
unsigned long timeoutTime = 5000000UL;


void setup(){
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    Serial.begin(115200);
}

void timing(){

    mills = millis();

    if (micros() < 1000000) {
        microsInContext = micros();
    } else {
        microsInContext = micros() % 1000000;
    }

    totalSecs = micros() / 1000000;

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
    microsElapsed = micros() / 500000UL;

    timesMicrosElapsed = microsElapsed % 2;

    if (timesMicrosElapsed == 0) {
        digitalWrite(outputPin, HIGH);
    } else {
        digitalWrite(outputPin, LOW);
    }

}

void capture(){
    before = current;
    readings = digitalRead(inputPin);

    if (initialReadIf == false){
        initTime = micros();
        initRead = readings;
        before = readings;
        current = readings;
        initialReadIf = true;
    }

    current = readings;

    if (current != before) {
        thecaptured = true;
        levelItsAt[yolo] = readings;
        timeHappened[yolo] = micros();
        yolo++;
        //Serial.printf("%d,%d,%02d:%02d:%02d:%04lu\n", inputPin, readings, hours, mins, secs, millsInContext);
    } 
}

void printTing(){
    Serial.printf("Initial reading: %d, Initial Time: %lu, Transitions: %d\n", initRead, initTime, yolo);
    if (yolo > 0){
        Serial.printf("reading: %d, time(micros): %lu \n", levelItsAt[0], timeHappened[0]);
    }
    

    for(int c = 1; c < yolo; c++) {
        betweenEvents = timeHappened[c] - timeHappened[c - 1];
        Serial.printf("reading: %d, time(micros): %lu Time between last event:%lu \n", levelItsAt[c], timeHappened[c], betweenEvents);
    }

    Serial.printf("Reason for Stop: %s", reasonStop);
}

void loop(){

    if (yolo < tarEnv){
        makeSig();
        capture();
    }

    if (micros() - sTime >= timeoutTime){
        reasonStop = "TIMEOUT";
        printTing();
        printed = true;
    }

    if(yolo == tarEnv && printed == false){
        reasonStop = "FULL";
        printTing();
        printed = true;
    }
    
}

