/*
 * RFID Reader Test Code
 * Written by Kyle Finke and Nathaniel Brooke
 * Based on code from Parallax and djmatic (whoever that is)
 * 
 * RFID Sensor Connection:
 * VCC to 5v
 * ENABLE to digital pin 4
 * SOUT to RX1 (pin 19)
 * GND to ground
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

#define ENABLE_PIN 4

char code[10]; // Holds the code read from RFID tag

int  val = 0;
int bytesread = 0;

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
  Serial.println("Initialized");
  Serial1.begin(2400); // Initialize Serial to RFID reader
  pinMode(ENABLE_PIN, OUTPUT); // Set pin 4 as output for enable
  digitalWrite(ENABLE_PIN, LOW); // Activate the RFID reader
}


void loop() {

  if (Serial1.available() > 0) { // if data available from reader
    if ((val = Serial1.read()) == 10) { // check for header
      bytesread = 0;
      while (bytesread < 10) { // read 10 digit code
        if ( Serial1.available() > 0) {
          val = Serial1.read(); // read 1 digit of tag code 
          if ((val == 10) || (val == 13)) { // if header or stop bytes before the 10 digit reading
            break; // stop reading
          }
          code[bytesread] = val; // add the digit to the end of the code
          bytesread++; // ready to read next digit
        }
      }
      if (bytesread == 10) { // if 10 digit read is complete
        
        // Write to serial monitor
        Serial.print("Tag code is: ");
        Serial.print(code); // print the tag code
        
        // Write to LCD
        Serial3.write(12); // Clear LCD
        Serial3.println("Tag code is: ");
        Serial3.write(13); // Write newline to LCD
        Serial3.println(code); // print the tag code
      }
      bytesread = 0;
     }
  }
}

