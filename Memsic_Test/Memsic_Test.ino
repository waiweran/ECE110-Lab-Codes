/*
 * Memsic Dual-Axis Accelerometer Test
 * Written by Nathaniel Brooke
 * Adapted from Parallax
 * Look in Memsic Guide PDF for more info
 * 
 * Memsic Connection:
 * X Output to Pin 2
 * Y Output to Pin 3
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

#define X_PIN 2 // X output connected to pin 2
#define Y_PIN 3 // Y output connected to pin 3

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
}

void loop() { 
  
  // Read Memsic Accelerometer
  int pulseX = pulseIn(X_PIN, HIGH);  // Read X pulse  
  int pulseY = pulseIn(Y_PIN, HIGH);  // Read Y pulse

  // Display result on Serial Monitor
  Serial.print(pulseX);
  Serial.print("\t");
  Serial.print(pulseY);

  // Display result on LCD
  Serial3.write(12); // Clear LCD
  Serial3.print(pulseX); // Print X value
  Serial3.print("   "); // Print spaces
  Serial3.print(pulseY); // Print Y value


  // Check if sensor is flat and stationary
  if(pulseX < 5100 && pulseX > 4900 // Flat in X
      && pulseY < 5100 && pulseY > 4900) { // Flat in Y
    Serial.print("\t\tFlat");
    Serial3.write(13); // Write newline to LCD
    Serial3.print("Flat"); // Print string to LCD
  }
  
  Serial.println(); // End of line on Serial Monitor

  delay(200);
}
