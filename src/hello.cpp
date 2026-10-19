#include <Arduino.h>

int a = 13;  

void setup(){
    pinMode(a, OUTPUT);
}

void loop(){
    digitalWrite(a, LOW);
    delay(1000);
    digitalWrite(a, HIGH);
    delay(1000);
}