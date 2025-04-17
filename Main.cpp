#include <LiquidCrystal.h>
#include <Servo.h>

// Initialize the LCD with the interface pins
// Based on your schematic: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define pins
const int greenLedPin = 8;    // Green LED pin
const int redLedPin = 9;      // Red LED pin
const int servoPin = 10;      // Servo pin
const int sensorPin = A0;     // Analog sensor input pin

// Threshold for determining reusable waste
const int reusableThreshold = 500;  // Adjust this value based on your sensor

// Create servo object
Servo sorterServo;

// Servo positions
const int leftPosition = 30;   // Position for reusable waste
const int rightPosition = 150; // Position for non-reusable waste

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.begin(16, 2);
  
  // Set up LED pins
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  
  // Attach servo
  sorterServo.attach(servoPin);
  
  // Initial servo position (neutral)
  sorterServo.write(90);
  
  // Initial message on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waste Sorter");
  lcd.setCursor(0, 1);
  lcd.print("Ready...");
  
  // All LEDs off initially
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  
  delay(2000);
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
  
  // Clear display
  lcd.clear();
  
  // Check if waste is reusable
  if (sensorValue > reusableThreshold) {
    // Reusable waste detected
    
    // Display on LCD
    lcd.setCursor(0, 0);
    lcd.print("Reusable");
    lcd.setCursor(0, 1);
    lcd.print("Waste Detected");
    
    // Green LED on, Red off
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    
    // Move servo to left
    sorterServo.write(leftPosition);
  } 
  else {
    // Non-reusable waste detected
    
    // Display on LCD
    lcd.setCursor(0, 0);
    lcd.print("Non-Reusable");
    lcd.setCursor(0, 1);
    lcd.print("Waste Detected");
    
    // Red LED on, Green off
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    
    // Move servo to right
    sorterServo.write(rightPosition);
  }
  
  // Wait before next reading
  delay(2000);
}