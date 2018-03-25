/*
 * Hall Effect Sensor Test Code
 * Written by Nathaniel Brooke
 * With help from Neel Prabhu
 * 
 * Hall Effect Sensor Connection: CAUTION MAY BE WRONG
 * Left pin to 5V
 * Center pin to Ground
 * Right pin to A3 (Analog pin 3)
 * 
 *  Sensor Top View: 
 *          __________
 *    LEFT  \________/  RIGHT
 *    
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

#define SENSOR_PIN 3

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
}

void loop() {
  // Read the magnet strength from the sensor
  int magStrength = analogRead(SENSOR_PIN);

  // Display measurement on serial monitor
  Serial.print("Hall Effect Reading - ");
  Serial.print(magStrength);

  // Display measurement on LCD
  Serial3.write(12); // Clear LCD
  Serial3.print(magStrength); // Print number to LCD

  // Check if magnet found nearby
  if (magStrength > 600 || magStrength < 400) {
    Serial.print("   Magnet Found");
    Serial3.write(13); // Write newline to LCD
    Serial3.write("Magnet Found");
  }

  Serial.println(); // Print newline to serial monitor
  
  delay(100);
}
