/*
 * readControls.ino
 * 
 * This file contains functions to parse control data
 */

#include "ServerDefines.h"


/*
 * Parse sensor data
 */
void readSensor(char receivedChar, int sensor) {
  int currDataSize = sensorDataSize[sensor];
  bool isReading = isReadingSensor[sensor];
  
  if (receivedChar == SENSOR_CHARS[sensor]) {
//    Serial.print("SENSOR ");
//    Serial.print(sensor);
//    Serial.println(" START");
    resetSensorVars(sensor);
    isReadingSensor[sensor] = true;
  } else if (isAlpha(receivedChar) && isReading && currDataSize) {
//    Serial.print("SENSOR ");
//    Serial.print(sensor);
//    Serial.println(" RECEIVED.............");
    finishReadingSensor(sensor, currDataSize);
  } else if (isReading) {
//    Serial.print("SENSOR ");
//    Serial.print(sensor);
//    Serial.print(" RECEIVE CHAR ");
//    Serial.println(currDataSize);
    readChar(receivedChar, sensor, currDataSize);
  }
}


void readChar(char receivedChar, int sensor, int currDataSize) {
  if (currDataSize < DATA_BUFFER_SIZE) {
    if (receivedChar == '/' || receivedChar == '?')
      sensorData[sensor][currDataSize++] = '.';
    else
      sensorData[sensor][currDataSize++] = receivedChar;
    sensorDataSize[sensor] = currDataSize;
  }
}


void finishReadingSensor(int sensor, int currDataSize) {
//  Serial.println("Finished reading");
  sensorData[sensor][currDataSize] = '\0';  // null terminate
  receivedSensorData[sensor] = true;
  isReadingSensor[sensor] = false;
}


void resetSensorVars(int sensor) {
//  Serial.println("Resetting");
  receivedSensorData[sensor] = false;
  sensorDataSize[sensor] = 0;
}
