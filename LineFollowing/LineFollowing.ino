#include <Servo.h>                         // Use Servo library

/*
 * Line Following Code for ECE 110
 * Written by Nathaniel Brooke
 * Uses RCtime code from Parallax
 * 
 * This code uses 3 QTIs
 * 
 * Servo Connections:
 * Left servo to pin 13
 * Right servo to pin 12
 * 
 * QTI Connections:
 * Left QTI to digital pin 5
 * Center QTI to digital pin 6
 * Right QTI to digital pin 7
 */

#define LEFT_QTI 5                         // Define left QTI pin
#define MID_QTI 6                          // Define middle QTI pin
#define RIGHT_QTI 7                        // Define right QTI pin

#define THRESHOLD 100;                     // Constant that differentiates between light and dark

Servo servoL;                              // Define left servo
Servo servoR;                              // Define right servo

// Runs at start
void setup() {
  Serial.begin(9600);                      // Set data rate to 9600 bps
  servoL.attach(13);                       // Attach left servo to pin 13
  servoR.attach(12);                       // Attach right servo to pin 12
  lineFollow();                            // Run line following
}

// Runs forever after setup
void loop() {}

// Runs the line following routine
void lineFollow() {

  while (true) {                           // Loop for continuous following of line
    long tR = rcTime(RIGHT_QTI);           // Left sensor reading
    long tM = rcTime(MID_QTI);             // Middle sensor reading
    long tL = rcTime(LEFT_QTI);            // Right sensor reading

    Serial.print(tL); Serial.print(" ");   // Display left sensor value
    Serial.print(tM); Serial.print(" ");   // Display middle sensor value
    Serial.println(tR);                    // Display right sensor vaule
    
    boolean lightR = tR < THRESHOLD;       // Is the right sensor over light surface?
    boolean lightM = tM < THRESHOLD;       // Is the middle sensor over light surface?
    boolean lightL = tL < THRESHOLD;       // Is the left sensor over light surface?

    int vL, vR;                            // Initialize velocities
    
    if(lightL && lightM && lightR){        // Light Light Light
      vL = -100;                           // Overshot line, go back
      vR = -100;
    }
    else if(lightL && lightM && !lightR){  // Light Light Dark
      vL = 100;                            // hard right
      vR = -10;
    }
    else if(lightL && !lightM && lightR){  // Light Dark  Light
      vL = 100;                            // go straight
      vR = 100;
    }
    else if(lightL && !lightM && !lightR){ // Light Dark  Dark
      vL = 100;                            // soft right
      vR = 50;
    }
    else if(!lightL && lightM && lightR){  // Dark  Light Light
      vL = -10;                            // hard left
      vR = 100;
    }
    else if(!lightL && lightM && !lightR){ // Dark  Light Dark
      vL = vL;                             // hope erroneous reading goes away
      vR = vR;
    }
    else if(!lightL && !lightM && lightR){ // Dark  Dark  Light
      vL = 50;                             // soft left
      vR = 100;
    }
    else {                                 // Dark  Dark  Dark with end
      servoL.writeMicroseconds(1500);      // stop and exit
      servoR.writeMicroseconds(1500);

      return;
    }
    servoL.writeMicroseconds(1500 + vL);   // Write velocity to left servo
    servoR.writeMicroseconds(1500 - vR);   // Write velocity to right servo
  }
}

// rcTime function at pin returns decay time
long rcTime(int pin) {
  pinMode(pin, OUTPUT);                    // Charge capacitor
  digitalWrite(pin, HIGH);                 // by setting pin ouput-high
  delayMicroseconds(230);                  // for 230 us
  pinMode(pin, INPUT);                     // Set pin to input
  digitalWrite(pin, LOW);                  // with no pullup
  long time  = micros();                   // Mark the time
  while (digitalRead(pin));                // Wait for voltage < threshold
  time = micros() - time;                  // Calculate decay time
  return time;                             // Return decay time
}
