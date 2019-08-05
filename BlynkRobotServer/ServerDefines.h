
/***** Global Defines ****/ 

#ifndef SERVERDEFINES_H
#define SERVERDEFINES_H

// Blynk app auth token
const char AUTH_TOKEN[] = "52d88fb094124f37ae828c1cb9ee49da";

// wiFi credentials
const char NETWORK_NAME[] = "MySpectrumWiFibc-2G";  //FiOS-2ZORX";
const char NETWORK_PASSWORD[] = "lighttruck899";  //"use2582donut606oak";


const int NUM_SENSORS = 3;

const int SENSE_IR_LEFT  = 0;
const int SENSE_IR_RIGHT = 1;
const int SENSE_DISTANCE = 2;

const byte SENSORS[NUM_SENSORS] = {
  SENSE_IR_LEFT,
  SENSE_IR_RIGHT,
  SENSE_DISTANCE};

const char SENSOR_CHARS[NUM_SENSORS] = {'A', 'B', 'C'};

const int DATA_BUFFER_SIZE = 15;


bool isReadingSensor[NUM_SENSORS] = {false, false, false};
int sensorDataSize[NUM_SENSORS] = {0, 0, 0};
bool receivedSensorData[NUM_SENSORS] = {false, false, false};
char sensorData[NUM_SENSORS][DATA_BUFFER_SIZE];

#endif
