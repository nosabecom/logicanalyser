#include <Arduino.h>

// Pins
int ledPin = 1;
int buttonPin = 2;
int potentiometerPin = 3;
int displayPins[8] = {4, 5, 6, 7, 8, 9, 10, 11};

// Variables
int potentiometerRead = 0;
int timesButtonPressed = 0;
int buttonState = 0;
int currentButtonState = 0;
int previousButtonState = 0;
int realButtonState = 0;
void setup(){
    pinMode(buttonPin, INPUT_PULLDOWN);
    pinMode(potentiometerPin, INPUT);
    pinMode(ledPin, OUTPUT);
    for (int i = 0; i < 8; i++) {
        pinMode(displayPins[i], OUTPUT);
    }
}

void forward(){
    digitalWrite(ledPin, LOW);
    potentiometerRead = analogRead(potentiometerPin);
    potentiometerRead = map(potentiometerRead, 0, 4095, 0, 7);
    
    for (int c = 0; c <= 7; c++) {
        if (potentiometerRead >= c){
            digitalWrite(displayPins[c], HIGH);
        } else {
            digitalWrite(displayPins[c], LOW);
        }
    }
}

void backward(){
    digitalWrite(ledPin, HIGH);
    potentiometerRead = analogRead(potentiometerPin);
    potentiometerRead = map(potentiometerRead, 0, 4095, 7, 0);

    for (int c = 7; c >= 0; c--) {
        if (potentiometerRead <= c){
            digitalWrite(displayPins[c], HIGH);
        } else {
            digitalWrite(displayPins[c], LOW);
        }
    }
}



void loop(){
    previousButtonState = currentButtonState;
    
    buttonState = digitalRead(buttonPin);

    if (buttonState == 1){
        currentButtonState = 1;       
    } else {
        currentButtonState = 0;
    }

    if (previousButtonState == currentButtonState){
        realButtonState = 0;
    } else{
        realButtonState = 1;
    }

    if (realButtonState == 0){
        forward();
    } else if (realButtonState == 1){
        backward();
    }
    
}
