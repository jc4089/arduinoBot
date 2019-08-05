/*******************************
 Softservo.ino
 software servo control without using timers
 note that these functions block until complete
*******************************/ 

#include "RobotDefines.h"


void softServoAttach() {
  pinMode(SERVO_PIN, OUTPUT); 
}


// writes given angle to servo for given delay in milliseconds
void softServoWrite(int angle, long servoDelay) {
  int pulsewidth = map(angle, 0, 180, 544, 2400); // width in microseconds
  do {
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(SERVO_PIN, LOW);
    delay(20); // wait for 20 milliseconds
    servoDelay -= 20;
  } while(servoDelay >=0);
}
