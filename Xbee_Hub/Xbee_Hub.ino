/* 
 * XBee Hub Code
 * Used in Conjunction with XBee Test
 * Written by Nathaniel Brooke
 * 
 * XBee Connection:
 * DOUT to RX2 (pin 17)
 * DIN to TX2 (pin 16)
 */

void setup() {
  Serial2.begin(9600); // Initialize Serial to XBee
  delay(500);
}

void loop() {
  if(Serial2.available()) { // Wait for XBee to receive
    char incoming = Serial2.read(); // Read character from XBee
    Serial2.print((char)(incoming + 1)); // Write next character to XBee
  }
  delay(50);
}

