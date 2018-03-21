#include <Servo.h> // Use Servo library

/*
 * Servo Calibration Code
 * Written by Nathaniel Brooke
 * For servos on pins 12 and 13
 */

Servo servo12; // Pin 12 Servo
Servo servo13; // Pin 13 Servo

void setup() {
  servo12.attach(12); // Attach servo on pin 12
  servo13.attach(13); // Attach servo on pin 13
  servo12.writeMicroseconds(1500); // Servo on pin 12 to still
  servo13.writeMicroseconds(1500); // Servo on pin 13 to still
}

void loop() {}
