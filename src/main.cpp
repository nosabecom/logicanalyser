#include <Arduino.h>

int a = 14;
int b = 32;  

void setup(){
    pinMode(a, INPUT_PULLDOWN);
    pinMode(b, OUTPUT);
}

void loop(){
    int s = digitalRead](a);
    if (s == 1){
        digitalWrite(b, HIGH);
    } else if (s == 0) {
        digitalWrite(b, LOW);
    } 
}