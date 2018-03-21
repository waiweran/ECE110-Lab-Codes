#include <Servo.h> // Use Servo library

/*
 * Servo Motor Test Code
 * Written by Nathaniel Brooke
 * Tests servos on pins 12 and 13
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

Servo servo12; // Pin 12 Servo
Servo servo13; // Pin 13 Servo

void setup() {
  servo12.attach(12); // Attach servo on pin 12
  servo13.attach(13); // Attach servo on pin 13
  servo12.writeMicroseconds(1500); // Servo on pin 12 to still
  servo13.writeMicroseconds(1500); // Servo on pin 13 to still
}

void loop() {

  // Servos Still
  Serial3.write(12); // Clear LCD
  Serial3.print("Servos Still"); // Print servo state
  Serial.println("Servos Still");
  servo12.writeMicroseconds(1500); // Servo 12 still
  servo13.writeMicroseconds(1500); // Servo 13 still
  delay(300);

  // Servo 12 Moving
  Serial3.write(12); // Clear LCD
  Serial3.print("Servo 12 Moving"); // Print servo state
  Serial.println("Servo 12 Moving");
  servo12.writeMicroseconds(1300); // Servo 12 moving
  delay(300);

  // Servo 13 Moving
  Serial3.write(12); // Clear LCD
  Serial3.print("Servo 13 Moving"); // Print servo state
  Serial.println("Servo 13 Moving");
  servo12.writeMicroseconds(1500); // Servo 12 still
  servo13.writeMicroseconds(1700); // Servo 13 moving
  delay(700);

  // Servos Drive Together
  Serial3.write(12); // Clear LCD
  Serial3.print("Moving Together"); // Print servo state
  Serial.println("Moving Together");
  servo12.writeMicroseconds(1300); // Servo 12 moving
  servo13.writeMicroseconds(1700); // Servo 13 moving
  delay(1000);
}
