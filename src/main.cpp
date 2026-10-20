#include <Arduino.h>

// replace all numbers with real pins
int ledPin = 1;
int buttonPin = 2;
int potentiometerPin = 3;
int displayPins[8] = {4, 5, 6, 7, 8, 9, 10, 11};
int potentiometerRead;

/*void makemoney(){
    if (buttonPin >= 0){
        digitalWrit
    }
}*/

void setup(){
    pinMode(buttonPin, INPUT_PULLDOWN);
    pinMode(potentiometerPin, OUTPUT)
    pinMode(ledPin, OUTPUT);
    for (i = 0, i < 8; i++) {
        pinMode(displayPins[i], OUTPUT)
    }

}

void loop(){
    potentiometerRead = analogRead(potentiometerPin);
    potentiometerRead > 0
    if (potentiometerRead >= 0 && <= 511){
        digitalWrite(displayPins[0], HIGH));
    } else{
        digitalWrite(displayPins[1], LOW));
    }

}