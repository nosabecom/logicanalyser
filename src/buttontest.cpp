#include <Arduino.h>
//pins
int ledPin = 21;
int buttonPin = 33;

//variables
int buttonPressed;

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    buttonPressed = digitalRead(buttonPin);


    if (buttonPressed > 0){
        digitalWrite(ledPin, HIGH);
    } else{
        digitalWrite(ledPin, LOW);
    }
    
    delay(500);
    Serial.print("Reading: ");
    Serial.println(buttonPressed);
}