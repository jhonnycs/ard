/*
  APDS-9960 - Proximity Sensor

  This example reads proximity data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints the proximity value to the Serial Monitor
  every 100 ms.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

int ledState = LOW;
unsigned long previousMillis = 0;

const long intervalLong = 1000;
const long intervalMed = 500;
const long intervalShort = 100;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    int proximity = APDS.readProximity();

    // print value to the Serial Monitor
    Serial.println(proximity);
    
    if (proximity > 150) {
      if (currentMillis - previousMillis >= intervalLong) {
        previousMillis = currentMillis;
        
        // if the LED is off turn it on and vice-versa:
        ledState = !ledState;
        
        // set the green LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDG, ledState);
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDB, HIGH);
      }
    } else if (proximity > 50) {
      if (currentMillis - previousMillis >= intervalMed) {
        previousMillis = currentMillis;
        
        // if the LED is off turn it on and vice-versa:
        ledState = !ledState;
        
        // set the blue LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDB, ledState);
      }
    } else {
      if (currentMillis - previousMillis >= intervalShort) {
        previousMillis = currentMillis;
        
        // if the LED is off turn it on and vice-versa:
        ledState = !ledState;
        
        // set the red LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDR, ledState);
        digitalWrite(LEDB, HIGH);
      
      }
    }

  // wait a bit before reading again
  delay(100);
  }
}
