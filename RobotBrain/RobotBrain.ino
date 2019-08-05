/*
 * Robot Brain
 */

#include <SoftwareSerial.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

#include "RobotMotor.h"
#include "RobotDefines.h"


SoftwareSerial mySerial(10, 11); // RX, TX

// Servo myServo;


void setup() {
  Serial.begin(57600);
  mySerial.begin(57600);

  // myServo.attach(servoPin);
  // myServo.write(0);

  sonarBegin();
  lookBegin();
  moveBegin();

  softServoWrite(90, 2000);
  moveSetSpeed(MIN_SPEED + 10); //speedTable[5]);
}


void loop() {
  int sensorAReading = analogRead(SENSE_IR_LEFT);
  int sensorBReading = analogRead(SENSE_IR_RIGHT);

  float distanceReading = getDistance();

  String str = String("Left hand: ") + String(sensorAReading) + \
    String("  Right hand: ") + String(sensorBReading) + \
    String("  Eyes: ") + String(distanceReading);
  
  String encodedStr = String("A") + String(sensorAReading) + \
    String("B") + String(sensorBReading) + \
    String("C") + String(distanceReading) + String("E");
  
//  Serial.println(str);
  mySerial.print(encodedStr);
//  delay(100);  // to better synchronize with server receiving data

  getControlData();

  // control servo
  if (receivedServoData) {
    String servoDataStr = String(servoData);
    if (stringIsFloat(servoDataStr)) {
      float servoDataFloat = 180 - servoDataStr.toFloat();
      Serial.print("Turning to ");
      Serial.println(servoDataFloat);
      softServoWrite(servoDataFloat, 10);
      // myServo.write(servoDataFloat);
    }
    resetServoVars();
  }

  // switch explore mode on and off
  if (receivedAutoFlagData) {
    String autoFlagDataStr = String(autoFlagData);
    // Serial.println("Received auto " + autoFlagDataStr);
    if (stringIsFloat(autoFlagDataStr)) {
      if (autoFlagDataStr == "1") {
        Serial.println("Explore mode enabled...");
        exploreMode = true;
      } else if (autoFlagDataStr == "0") {
        Serial.println("Explore mode disabled...");
        exploreMode = false;
      }
    }
    resetAutoFlagVars();
  }

  // control motors
  if (receivedJoystickData) {
    String joystickXDataStr = String(joystickXData);
    String joystickYDataStr = String(joystickYData);
    // Serial.print("X = ");
    // Serial.print(joystickXDataStr);
    // Serial.print(", Y = ");
    // Serial.println(joystickYDataStr);

    if (stringIsFloat(joystickXDataStr) && stringIsFloat(joystickYDataStr)) {
      float x = joystickXDataStr.toFloat();
      float y = joystickYDataStr.toFloat();
      xy2moveState(x, y);
    }
    
    resetJoystickVars();
  }

  if (exploreMode) {
//    Serial.println("Moving straight...");
    moveForward();

    // look around
    roam();
  } else {
    if (moveState == MOV_FORWARD) {
//      Serial.println("Moving straight...");
      moveForward();
    } else if (moveState == MOV_RIGHT) {
//      Serial.println("Moving right...");
      moveRight();
    } else if (moveState == MOV_LEFT) {
//      Serial.println("Moving left...");
      moveLeft();
    } else if (moveState == MOV_STOP && prevMoveState != MOV_STOP) {
//      Serial.println("Stopping motor...");
      prevMoveState = MOV_STOP;
      moveStop();
    }
  }
}


bool stringIsFloat(String str) {
  // Serial.println("Running stringIsFloat...");
  int signCount = 0;
  int decPointCount = 0;
  int digitCount = 0;
  int otherCount = 0;
  
  for (int j = 0; j < str.length(); j++) {
    char ch = str.charAt(j);
    if (j == 0 && (ch == '-' || ch == '+')) {
      // leading sign
      signCount++;
    } else if (ch >= '0' && ch <= '9') {
      // digit
      digitCount++;
    } else if (ch == '.') {
      //decimal point
      decPointCount++;
    } else {
      //that's bad :(
      otherCount++;
    }
  }
  
  return (signCount <= 1 && decPointCount <= 1 && digitCount >= 1 && otherCount == 0);
}


void getControlData() {
  while (mySerial.available()) {
    char receivedChar = mySerial.read();
    // Serial.print("Data = ");
    // Serial.println(receivedChar);

    // only read servo and joystick data
    // when not in explore mode
    if (!exploreMode) {
      // read servo
      readServo(receivedChar);
  
      // read joystick
      readJoystickData(receivedChar);
    }

    // always read button to turn on and off
    // explore mode
    readAutoFlag(receivedChar);
  }
}


void xy2moveState(float x, float y) {
  if (x > 510 && x < 513 && y < 513) {
    changeMoveState(MOV_STOP);
  } else if (y >= 513) {
    if (x < 400) {
      // Serial.println("Changing move state to left...");
      changeMoveState(MOV_LEFT);
    } else if (x > 600) {
      // Serial.println("Changing move state to right...");
      changeMoveState(MOV_RIGHT);
    } else {
      // Serial.println("Changing move state to forward...");
      changeMoveState(MOV_FORWARD);
    }
  }
}
