/*
 * QTI Test Code
 * Written by Nathaniel Brooke
 * rcTime function from Parallax
 * 
 * QTI Connection:
 * B to Ground
 * R to digital pin 7
 * W to 5V
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
}

void loop() {
  int time = rcTime(7); // Read QTI on pin 7
  
  Serial.print("QTI Reading: "); // Print reading to Serial Monitor
  Serial.print(time);
  Serial3.write(12); // Clear LCD
  Serial3.print("QTI: "); // Print QTI reading to LCD
  Serial3.print(time);
  Serial3.write(13); // Write newline to LCD

  // Detected nothing
  if(time > 10000) {
    Serial.println("\tDetected Nothing");
    Serial3.print("Nothing");
  }

  // Detected white surface
  else if(time < 100) { // Detected
    Serial.println("\t\tDetected White Surface");
    Serial3.print("White");
  }

  // Detected black surface
  else if(time > 1000) {
    Serial.println("\tDetected Black Surface");
    Serial3.print("Black");
  }

  // Detected something in between white and black
  else {
    Serial.println("\tDetected Gray Surface");
    Serial3.print("Gray");

  }
  
  delay(100);
}

/*
 * rcTime function at pin returns decay time
 * From Parallax website
 */
long rcTime(int pin) {
  pinMode(pin, OUTPUT);      // Charge capacitor
  digitalWrite(pin, HIGH);   // by setting pin ouput-high
  delayMicroseconds(230);    // for 230 us
  pinMode(pin, INPUT);       // Set pin to input
  digitalWrite(pin, LOW);    // with no pullup
  long time  = micros();     // Mark the time
  while (digitalRead(pin));  // Wait for voltage < threshold
  time = micros() - time;    // Calculate decay time
  return time;               // Return decay time
}
