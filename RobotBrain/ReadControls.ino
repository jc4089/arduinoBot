/*
 * readControls.ino
 * 
 * This file contains functions to parse control data
 */

#include "RobotDefines.h"


/*
 * Parse servo control
 */
void readServo(char receivedChar) {
  // Serial.println(isReadingServo);
  if (receivedChar == servoChar) {
    // Serial.println("SERVO Path 1");
    resetAllControlVars();
    isReadingServo = true;
  } else if (isAlpha(receivedChar) && servoDataSize) {
    // Serial.println("SERVO Path 2");
    receivedServoData = true;
  } else if (isReadingServo) {
    // Serial.println("SERVO Path 3");
    if (receivedChar == '/' || receivedChar == '?') {
      servoData[servoDataSize++] = '.';
    } else {
      servoData[servoDataSize++] = receivedChar;
    }
  }
}


/*
 * Parse auto flag
 */
void readAutoFlag(char receivedChar) {
  if (receivedChar == autoFlagChar) {
    // Serial.println("AUTO FLAG Path 1");
    resetAllControlVars();
    isReadingAutoFlag = true;
  } else if (isAlpha(receivedChar) && autoFlagDataSize) {
    // Serial.println("AUTO FLAG Path 2");
    receivedAutoFlagData = true;
  } else if (isReadingAutoFlag) {
    // Serial.println("AUTO FLAG Path 3");
    autoFlagData[autoFlagDataSize++] = receivedChar;
  }
}


/*
 * Parse joystick controls
 */
void readJoystickData(char receivedChar) {
  if (receivedChar == joystickXChar) {
    // Serial.println("JOYSTICK Path 1");
    resetAllControlVars();
    isReadingX = true;
    isReadingY = false;
  } else if (receivedChar == joystickYChar && isReadingX) {
    // Serial.println("JOYSTICK Path 2");
    isReadingY = true;
    isReadingX = false;
  } else if (isAlpha(receivedChar) && xDataSize && yDataSize) {
    // Serial.println("JOYSTICK Path 3");
    receivedJoystickData = true;
  } else if (isReadingX) {
    // Serial.println("JOYSTICK Path 4");
    if (receivedChar == '/' || receivedChar == '?') {
      joystickXData[xDataSize++] = '.';
    } else {
      joystickXData[xDataSize++] = receivedChar;
    }
  } else if (isReadingY) {
    // Serial.println("JOYSTICK Path 5");
    if (receivedChar == '/' || receivedChar == '?') {
      joystickYData[yDataSize++] = '.';
    } else {
      joystickYData[yDataSize++] = receivedChar;
    }
  }
}


void resetAllControlVars() {
  // reset all control variables
  resetServoVars();
  resetAutoFlagVars();
  resetJoystickVars();
}


void resetServoVars() {
  // reset global servo variables
  servoDataSize = 0;
  isReadingServo = false;
  receivedServoData = false;
  memset(servoData, 0, sizeof(servoData));
}


void resetAutoFlagVars() {
  // reset global autoFlag variables
  autoFlagDataSize = 0;
  isReadingAutoFlag = false;
  receivedAutoFlagData = false;
  memset(autoFlagData, 0, sizeof(autoFlagData));
}


void resetJoystickVars() {
  // reset global joystick variables
  xDataSize = 0;
  yDataSize = 0;
  isReadingX = false;
  isReadingY = false;
  receivedJoystickData = false;
  memset(joystickXData, 0, sizeof(joystickXData));
  memset(joystickYData, 0, sizeof(joystickYData));
}
