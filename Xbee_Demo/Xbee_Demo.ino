/* 
 * XBee Demo Code for Sentry Bot
 * Written by Nathaniel Brooke
 * 
 * XBee Connection:
 * DOUT to RX2 (pin 17)
 * DIN to TX2 (pin 16)
 */

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial2.begin(9600); // Initialize Serial to XBee
  delay(500);
}
void loop() {
  if(Serial.available()) { // Is data available from computer?
    char outgoing = Serial.read(); // Read character from computer
    Serial2.print(outgoing); // Send the read character to XBee
    Serial.print("Sent "); // Print info for sent character
    Serial.println(outgoing); // send to Serial Monitor
  }
  if(Serial2.available()) { // Is data available from XBee?
    char incoming = Serial2.read(); // Read character
    Serial.print("Received "); // Print info for character
    Serial.println(incoming); // send to Serial Monitor
  }
  delay(50);
}

