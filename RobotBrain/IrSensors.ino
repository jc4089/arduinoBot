
/****************************
   ir reflectance sensor code   
****************************/

#include "RobotDefines.h"

int irSensorAmbient[NBR_SENSORS]; // sensor value with no reflection
int irSensorReflect[NBR_SENSORS]; // value considered detecting an object
int irSensorEdge[NBR_SENSORS];    // value considered detecting an edge
boolean isDetected[NBR_SENSORS] = {false, false}; // set true if object detected


void irSensorBegin() {
  for (int sensor = 0; sensor < NBR_SENSORS; sensor++)
     irSensorCalibrate(sensor);
}


// calibrate for ambient light 
void irSensorCalibrate(byte sensor) {
  int ambient = analogRead(IR_SENSOR[sensor]); // get ambient level
  irSensorAmbient[sensor] = ambient; 
  
  // precalculate the levels for object and edge detection
  irSensorReflect[sensor] = ambient - IR_REFLECT_THRESHOLD;
  irSensorEdge[sensor] = ambient + IR_EDGE_THRESHOLD;
}


// returns true if an object reflection detected on the given sensor
// the sensor parameter is the index into the sensor array
boolean irSensorDetect(int sensor) {
  boolean result = false; // default value
  int value = analogRead(IR_SENSOR[sensor]); // get IR light level
  if (value <= irSensorReflect[sensor]) {
       result = true; // object detected (lower value means more reflection)
       if (isDetected[sensor] == false) { // only print on initial detection
         Serial.print(locationString[sensor]);         
         Serial.println(" object detected");
       }
   }
   isDetected[sensor] = result; 
   return result;
}


boolean irEdgeDetect(int sensor) {
  boolean result = false; // default value
  int value = analogRead(IR_SENSOR[sensor]); // get IR light level
  if (value >= irSensorEdge[sensor]) {
       result = true; // edge detected (higher value means less reflection)
       if (isDetected[sensor] == false) { // only print on initial detection
         Serial.print(locationString[sensor]);         
         Serial.println(" edge detected");
       }
   }
   isDetected[sensor] = result; 
   return result;
}
