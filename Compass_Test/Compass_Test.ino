#include <Wire.h> // Required for Compass Sensor

/*
 * HMC5883 Compass Sensor Test Code
 * Written by Nathaniel Brooke
 * Adapted from Parallax
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

// 7-bit address of HMC5883 compass, change if using multiple
#define Addr 0x1E

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
  startCompass(); // Start the Compass Sensor
}

void loop() {
  // Read Compass sensor
  int x, y, z; // Variables to store sensor readings
  readCompass(&x, &y, &z); // Read values from compass sensor

  // Print raw values to Serial Monitor
  Serial.print("X=");
  Serial.print(x);
  Serial.print(", Y=");
  Serial.print(y);
  Serial.print(", Z=");
  Serial.print(z);
  Serial.print("\t\t");

  // Print raw values to LCD
  Serial1.write(12); // Clear LCD
  Serial1.print(x);
  Serial1.print(" ");
  Serial1.print(y);
  Serial1.print(" ");
  Serial1.print(z);
  Serial1.write(13); // Write newline to LCD

  // Check for magnet
  if(x < -1000 || x > 1000 || y < -1000 || y > 1000 || z < -1000 || z > 1000) {
    Serial1.print("Magnet Found");
    Serial.print("Magnet Found");
  }
  Serial.println();

  delay(500);
}

/*
 * Initializes Communication with Compass
 */
void startCompass() {
  delay(100); // Power up delay
  Wire.begin(); // Initialize I2C 

  // Set operating mode to continuous
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}

/*
 * Loads values read from compass sensor
 * Magnetic field strength in X, Y, and Z
 */
void readCompass(int *x, int *y, int *z) {
    // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if (Wire.available() <= 6) {  // If 6 bytes available
    *x = Wire.read() << 8 | Wire.read();
    *z = Wire.read() << 8 | Wire.read();
    *y = Wire.read() << 8 | Wire.read();
  }
}

