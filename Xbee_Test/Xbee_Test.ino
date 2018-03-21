/* 
 * XBee Test Code
 * Used in Conjunction with XBee Hub
 * Written by Nathaniel Brooke
 * 
 * XBee Connection:
 * DOUT to RX2 (pin 17)
 * DIN to TX2 (pin 16)
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
  Serial2.begin(9600); // Initialize Serial to XBee
  Serial.println("Testing..."); // Write to Serial Monitor
  Serial3.write(12); // Clear LCD
  Serial3.print("Testing..."); // Print text to LCD
  char send = 'A'; // Starting character
  for (int i = 0; i < 20; i++) { // Send A, B, C, etc.
    Serial.print("Sending "); // Write to Serial Monitor
    Serial.println(send);
    Serial2.print(send++); // Send character to XBee, increment to next character
    for(int i = 0; !Serial2.available(); i++) { // Wait 1/2 second for response from hub
      delay(50);
        if(i > 10) { // Did not receive a response in 1/2 second
          Serial.println("Xbee Failed Test - No Response");
          Serial3.write(13); // Write newline to LCD
          Serial3.print("Failed - NR"); // Print failure text to LCD
          return; // End function, XBee failed
        }
      }
    delay(50);
    char incoming = Serial2.read(); // Read response from XBee
    Serial.print("Received "); // Print repsonse to Serial Monitor
    Serial.println(incoming);
    if (incoming != send) { // Check we received the right character back
      Serial.println("Xbee Failed Test - Wrong Character");
      Serial3.write(13); // Write newline to LCD
      Serial3.print("Failed - WC"); // Print failure text to LCD
      return; // End function, XBee failed
    }
  }
  Serial.println("Xbee is Good");
  Serial3.write(13); // Write newline to LCD
  Serial3.print("Good"); // Print failure text to LCD
}

void loop() {}

