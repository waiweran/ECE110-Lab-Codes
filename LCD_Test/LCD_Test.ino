/*
 * LCD Test Code
 * Written by Nathaniel Brooke
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

void setup() {
  Serial3.begin(9600); // Initialize Serial to LCD 
  Serial3.write(12); // Clear LCD
  Serial3.write("LCD Works if"); // Print string to LCD
  Serial3.write(13); // Write newline to LCD
  Serial3.write("it beeps"); // Print string to LCD

  Serial3.write(216); // Set tone to 4th scale
  Serial3.write(209); // Set tone length to 1/32 note (1/16 second)
  for (int i = 221; i < 232; i++) {
    Serial3.write(i); // Play A# thru G#, then rest
  }
}

void loop() {}
