#include <Wire.h>

#define Addr 0x1E               // 7-bit address of HMC5883 compass

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  delay(100);                   // Power up delay
  Wire.begin();

  // Set operating mode to continuous
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}

void loop() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if (Wire.available() <= 6) {  // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }

  // Print raw values
  Serial.print("X=");
  Serial.print(x);
  Serial.print(", Y=");
  Serial.print(y);
  Serial.print(", Z=");
  Serial.print(z);
  Serial.print("\t\t");

  Serial1.write(12);
  Serial1.print(x);
  Serial1.print(" ");
  Serial1.print(y);
  Serial1.print(" ");
  Serial1.print(z);
  Serial1.write(13);

  if(x < -1000 || x > 1000 || y < -1000 || y > 1000 || z < -1000 || z > 1000) {
    Serial1.print("Magnet Found");
    Serial.print("Magnet Found");
  }
  else if (x < -110 && x > -130 && y > 100) {
    Serial1.print("North");
    Serial.print("North");
  }  
  else if (x < -340 && x > -360) {
    Serial1.print("East");
    Serial.print("East");
  }  
  else if (x < -130 && x > -150 && y < 100) {
    Serial1.print("South");
    Serial.print("South");
  }  
  else if (x > 70 && x < 90) {
    Serial1.print("West");
    Serial.print("West");
  }
  Serial.println();

  delay(500);
}
