#include <SoftwareSerial.h> // ColorPAL uses this library

/*
 * ColorPAL Test Code
 * Written by Nathaniel Brooke
 * Adapted from Parallax
 * 
 * ColorPAL Connection:
 * sig to digital pin 11
 *
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

#define sig 11 // ColorPAL connected to pin 11

// Set up two software serials on the same pin.
SoftwareSerial serin(sig, 255);
SoftwareSerial serout(255, sig);

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  startColorpal();
}

void loop() {
  int red, grn, blu; // Values to be read from ColorPAL
  readData(&red, &grn, &blu); // Read from ColorPAL into red, grn, blu
  printValues(red, grn, blu); // Print color to LCD and Serial Monitor
}

/*
 * Starts the ColorPAL in the correct mode
 */
void startColorpal() {
  // Rest ColorPAL
  delay(200);
  pinMode(sig, OUTPUT);
  digitalWrite(sig, LOW);
  pinMode(sig, INPUT);
  while (digitalRead(sig) != HIGH);
  pinMode(sig, OUTPUT);
  digitalWrite(sig, LOW);
  delay(80);
  pinMode(sig, INPUT);
  delay(200);
  // Reset Complete
  serout.begin(4800);
  pinMode(sig, OUTPUT);
  serout.print("=(00 $ m)!"); // Loop print values, see ColorPAL documentation
  serout.end(); // Discontinue serial port for transmitting
  pinMode(sig, INPUT);
  serin.begin(4800); // Set up serial port for receiving
}

/*
 * Reads r, g, b values into red, grn, blu variables
 */
void readData(int *red, int *grn, int *blu) {
  char buffer[32];
  while (1) {
    if (serin.available() > 0) {
      // Wait for a $ character, then read three 3 digit hex numbers
      buffer[0] = serin.read();
      if (buffer[0] == '$') {
        for (int i = 0; i < 9; i++) {
          while (serin.available() == 0); // Wait for next input character
          buffer[i] = serin.read();
          if (buffer[i] == '$') // Return early if $ character encountered
            continue;
        }
        sscanf (buffer, "%3x%3x%3x", red, grn, blu);  // Pull the R, G, and B values from the data string
        delay(10);
        return; // Finished reading data
      }
    }
  }
}

/*
 * Print the RGB Values and the nearest color
 */
void printValues(int red, int grn, int blu) {
  // Print String containing red, green, blue colors
  char buffer[48];                               // create a buffer
  sprintf(buffer, "r = %4.4d    g = %4.4d    b = %4.4d", red, grn, blu);   //print the values into a buffer as formatted integers
  Serial.print(buffer);
  Serial.print("    ");
  sprintf(buffer, "%4.4d  %4.4d  %4.4d", red, grn, blu);   //print the values into a buffer as formatted integers
  Serial3.write(12);
  Serial3.println(buffer);

  // Print the closest color
  if (red > blu && grn > blu && (red - grn) < 70 && (red - grn) < 70) {
    // Empirically determined condition for yellow
    Serial.println("Yellow");
    Serial3.println("Yellow");
  }
  else if (red > grn && red > blu) { // More red than anything else
    Serial.println("Red");
    Serial3.println("Red");
  }  
  else if (blu > grn && blu > red) { // More green than anything else
    Serial.println("Blue");
    Serial3.println("Blue");
  }  
  else if (grn > red && grn > blu) { // More blue than anything else
    Serial.println("Green");
    Serial3.println("Green");
  }
  else {
    Serial.println("None");
    Serial3.println("None");
  }
}
