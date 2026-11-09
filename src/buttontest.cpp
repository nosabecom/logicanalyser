#include <Arduino.h>
//pins
extern int ledPin;
extern int buttonPin;

//variables
int buttonPressed;

void setup(){
    pinMode(buttonPin, INPUT_PULLDOWN);
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    buttonPressed = digitalRead(buttonPin);

    if (buttonPressed == 1){
        digitalWrite(ledPin, HIGH);
    } else{
        digitalWrite(ledPin, LOW);
    }
    
}