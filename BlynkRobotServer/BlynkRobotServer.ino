/*
 * Blynk Robot Server
 */

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "ServerDefines.h"

BlynkTimer timer;


void getSensorDataEvent() {
  getSensorData();
}


void getLeftIRSensorEvent() {
  if (receivedSensorData[SENSE_IR_LEFT]) {
    String leftIRSensor = String(sensorData[SENSE_IR_LEFT]);
//    Serial.println("Has received left IR data: " + leftIRSensor);
    Blynk.virtualWrite(V5, leftIRSensor);
    resetSensorVars(SENSE_IR_LEFT);
  }
}


void getRightIRSensorEvent() {
  if (receivedSensorData[SENSE_IR_RIGHT]) {
    String rightIRSensor = String(sensorData[SENSE_IR_RIGHT]);
//    Serial.println("Has received right IR data: " + rightIRSensor);
    Blynk.virtualWrite(V6, rightIRSensor);
    resetSensorVars(SENSE_IR_RIGHT);
  }
}


void getDistanceSensorEvent() {
  if (receivedSensorData[SENSE_DISTANCE]) {
    String distanceSensor = String(sensorData[SENSE_DISTANCE]);
//    Serial.println("Has received distance data: " + distanceSensor);
    Blynk.virtualWrite(V7, distanceSensor);
    resetSensorVars(SENSE_DISTANCE);
  }
}


BLYNK_WRITE(V8) {
  float pinValue = param.asFloat();
  Serial.print("S" + String(pinValue) + "B");
}


BLYNK_WRITE(V9) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  Serial.print("X" + String(x) + "Y" + String(y) + "Z");
}


BLYNK_WRITE(V10) {
  int pinValue = param.asInt();
  Serial.print("M" + String(pinValue) + "T");
}


void setup() {
  Serial.begin(57600);
  Blynk.begin(AUTH_TOKEN, NETWORK_NAME, NETWORK_PASSWORD);

  timer.setInterval(1L, getSensorDataEvent);
  timer.setInterval(1L, getLeftIRSensorEvent);
  timer.setInterval(1L, getRightIRSensorEvent);
  timer.setInterval(1L, getDistanceSensorEvent);
}


void loop() {
  Blynk.run();
  timer.run();  // initiate BlynkTimer
}


void getSensorData() {
  // for some strange reason, this needs to be a while instead of if!
  while (Serial.available()) {
    char receivedChar = Serial.read();
//    Serial.print("Data = ");
//    Serial.println(receivedChar);

    for (int sensor = 0; sensor < NUM_SENSORS; sensor++)
      readSensor(receivedChar, SENSORS[sensor]);
  }
}
