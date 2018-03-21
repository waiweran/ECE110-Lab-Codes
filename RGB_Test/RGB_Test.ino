#include <Adafruit_TCS34725.h> // Use the Adafruit RGB Sensor Library

/*
 * RGB Color Sensor Test Code
 * Written by Nathaniel Brooke
 * Adapted from Adafruit
 * 
 * Uses Adafruit Library
 * Add library to your environment:
 * Top Menu -> Sketch -> Include Library -> Manage Libraries
 * In the search bar, type "TCS34725"
 * Install the library that comes up
 * 
 * RGB Sensor Connection:
 * VIN to 5V
 * GND to GND
 * SDA to SDA (pin 20)
 * SCL to SCL (pin 21)
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

// The color sensor object
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
  
  if (tcs.begin()) { // Try to run the startup code
    Serial.println("Found Sensor"); // Found sensor, continue
    Serial3.write(12); // Clear LCD
    Serial3.print("Found Sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    Serial3.write(12); // Clear LCD
    Serial3.print("No Sensor");
    while (1); // Wait forever (until reset)
  }
  
}

void loop(void) {
  // Read from the RGB Sensor
  uint16_t r, g, b, overall; // Unsigned 16-bit integers for storing values
  tcs.getRawData(&r, &g, &b, &overall); // Read R, G, B values, and overall value

  // Library Calculations from Adafruit
  uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b); // Calculate color temperature using library function
  uint16_t lux = tcs.calculateLux(r, g, b); // Calculate lux using libary function

  // Print Data to Serial Monitor
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(overall, DEC); Serial.print(" ");

  // Print Data to LCD
  Serial3.write(12); // Clear LCD
  Serial3.print(r, DEC); Serial3.print(" ");
  Serial3.print(g, DEC); Serial3.print(" ");
  Serial3.print(b, DEC);
  Serial3.write(13); // Write newline to LCD

  // Print Closest Color
  printColor(r, g, b);

  delay(200);
}

/*
 * Prints the color that best matches what the RGB Sensor sees
 */
void printColor(uint16_t red, uint16_t grn, uint16_t blu) {
  if (red < 1000 && grn < 1000 && blu < 1000) { // All dim, nothing there
    Serial.println("None");
    Serial3.println("None");
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
