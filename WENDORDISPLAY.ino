#include <Arduino.h>
#include <TFT_eSPI.h>

int relay1Pin = 22; // Solenoid valve 1
int relay5Pin = 18;//dc motor 1 for mixing of milk and sugar
int relay2Pin = 23; // Solenoid valve 2
int relay6Pin = 20;//dc motor 2 for mixing of coffee and water
int relay3Pin = 21; // DC motor
int relay4Pin = 19; // Solenoid valve 3
int sensorPin = 34; // capacitive sensor
int pushbutton1Pin = 35; // Push button 1 
int pushbutton2Pin = 32; // Push button 2

// Variables to store button states
int pushbutton1State = 0;
int pushbutton2State = 0;

// Variables to store solenoid valve opening times
int solenoid1Time = 3000; // 3 second
int solenoid2Time = 3000; // 3 second

// Define TFT display pins
 int TFT_SCLK = 17;
 int TFT_SDA = 23;
 int TFT_RESET = 4;
 int TFT_DC = 5;

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // Initialize relays
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay5Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay6Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

// Initialize TFT display
  tft.begin();
  tft.setRotation(1); // Landscape orientation
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  int sensorState = digitalRead(sensorPin);
  
  // Read push button states
  button1State = digitalRead(pushbutton1Pin);
  button2State = digitalRead(pushbutton2Pin);
  
  // Update solenoid valve opening times based on button states
  
  if (button1State == HIGH) {
    solenoid1Time = 3000; // 3 seconds
  } else {
    solenoid1Time = 0; // 0 second
  }
  
  if (button2State == HIGH) {
    solenoid2Time = 3000; // 3 seconds
  } else {
    solenoid2Time = 0; // 0 second
  }
  
if (sensorState == HIGH) { // Object detected
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
  }
  
    // Display mixture content and delivery time on TFT display
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_WHITE);
    tft.println("Mixture Content:");
    tft.println("1:2");
    
    
    tft.setCursor(0, 100);
    tft.setTextColor(TFT_RED);
    tft.println("Delivery Time:");
    tft.println("  * 10:00 minutes");
  }
  
  delay(50); // Debounce time
}


    
