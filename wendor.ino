#include <Arduino.h>
#include<esp32-hal.h>
//milk and sugar stored in one tank and coffee in another. The tank 3 will contain the mixture of these two products
//level sensor is given to measure the level of liquids in the tanks
// Define relay pins
int relay1Pin = 22; // Solenoid valve 1
int relay5Pin = 18;//dc motor 1 for mixing of milk and sugar
int relay2Pin = 23; // Solenoid valve 2
int relay6Pin = 20;//dc motor 2 for mixing of coffee and water
int relay3Pin = 21; // DC motor
int relay4Pin = 19; // Solenoid valve 3
int sensorPin = 34; // capacitive sensor
int relay7Pin = 12; // Heater
int pushbutton1Pin = 35; // Push button 1 
int pushbutton2Pin = 32; // Push button 2
const int levelSensor1Pin = 25; // Level sensor 1
const int levelSensor2Pin = 26; // Level sensor 2
const int levelSensor3Pin = 27; // Level sensor 3

// Variables to store button states
int button1State = 0;
int button2State = 0;

// Variables to store solenoid valve opening times
int solenoid1Time = 1000; // 1 second
int solenoid2Time = 1000; // 1 second

// Variables to store level sensor states
int levelSensor1State = 0;
int levelSensor2State = 0;
int levelSensor3State = 0;

void setup()
 {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay5Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay6Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(relay7Pin, OUTPUT); // Heater relay pin
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(levelSensor1Pin, INPUT);
  pinMode(levelSensor2Pin, INPUT);
  pinMode(levelSensor3Pin, INPUT);
}

void loop() {
  int sensorState = digitalRead(sensorPin);
  
  // Read push button states
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  // Update solenoid valve opening times based on button states
  if (button1State == HIGH) {
    solenoid1Time = 2000; // 2 seconds
 } else {
    solenoid1Time = 1000; // 1 second
  }
  
  if (button2State == HIGH) {
    solenoid2Time = 3000; // 3 seconds
  } else {
    solenoid2Time = 1000; // 1 second
  }
  
  // Read level sensor states
  levelSensor1State = digitalRead(levelSensor1Pin);
  levelSensor2State = digitalRead(levelSensor2Pin);
  levelSensor3State = digitalRead(levelSensor3Pin);
  
  if (sensorState == HIGH && levelSensor1State == HIGH && levelSensor2State == HIGH && levelSensor3State == HIGH)
   {
    // Object detected and fluids present in all tanks
    // Run DC motor1 to mix milk and sugar
    digitalWrite(relay5Pin, HIGH);
    delay(2000); // Run for 2 seconds
    digitalWrite(relay5Pin, LOW);
   
    // Open solenoid valve 1 to drain it to the tank 3
    digitalWrite(relay1Pin, HIGH);
    delay(solenoid1Time); // Wait for solenoid1Time seconds

 // Run DC motor2 to mix coffee and water
    digitalWrite(relay6Pin, HIGH);
    delay(2000); // Run for 2 seconds
    digitalWrite(relay6Pin, LOW);
   
    
    // Open solenoid valve 2 to drain it to tank 3
    digitalWrite(relay2Pin, HIGH);
    delay(solenoid2Time); // Wait for solenoid2Time seconds
    
  // Turn on heater
    digitalWrite(relay7Pin, HIGH);

    
  // Run DC motor 3. Finally mix the things up 
    digitalWrite(relay3Pin, HIGH);
    delay(2000); // Run for 2 seconds
    digitalWrite(relay3Pin, LOW);
    
    // Open solenoid valve 3 to get the product 
    digitalWrite(relay4Pin, HIGH);
    delay(5000); // Wait for 5 second
    
  // Close all solenoid valves
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, LOW);
    digitalWrite(relay4Pin, LOW);
    digitalWrite(relay7Pin, LOW);
  }
  
  delay(50); // Debounce time
}