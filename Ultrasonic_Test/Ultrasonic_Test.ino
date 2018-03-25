/*
 * Ping))) Ultrasonic Sensor Test Code
 * Written by Nathaniel Brooke
 * Adapted from Parallax
 * 
 * PING Sensor Connection:
 * SIG to digital pin 8
 * 
 * LCD Connection:
 * RX to TX3 (pin 14)
 */

#define SIGNAL_PIN 8 // Pin the PING Sensor is connected to

void setup() {
  Serial.begin(9600); // Initialize Serial to computer
  Serial3.begin(9600); // Initialize Serial to LCD
}

void loop() {
  // Get the distance measurement (in cm) from sensor
  int distance = measureDistance(SIGNAL_PIN);

  // Display measurement on serial monitor
  Serial.print("Distance - ");
  Serial.print(distance);
  Serial.println(" cm");  

  // Display measurement on LCD
  Serial3.write(12); // Clear LCD
  Serial3.print(distance); // Print number to LCD
  Serial3.println(" cm"); // Print string to LCD
  
  delay(100);
}

int measureDistance(int signal) {
  // set pin as output so we can send a pulse
  pinMode(signal, OUTPUT);
  // set output to LOW
  digitalWrite(signal, LOW);
  delayMicroseconds(5);

  // now send the 5 microsecond pulse out to activate Ping)))
  digitalWrite(signal, HIGH);
  delayMicroseconds(5);
  digitalWrite(signal, LOW);

  // now we need to change the digital pin
  // to input to read the incoming pulse
  pinMode(signal, INPUT);

  // finally, measure the length of the incoming pulse
  unsigned long pulseduration = pulseIn(signal, HIGH);

  // divide the pulse length by half (there and back)
  pulseduration = pulseduration / 2;

  // convert to centimeters
  int distance = int(pulseduration / 29);

  // output the distance
  return distance;
}
