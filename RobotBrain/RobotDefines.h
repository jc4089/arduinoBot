
/***** Global Defines ****/ 

#ifndef ROBOTDEFINES_H
#define ROBOTDEFINES_H

// defines for locations of IR sensors
const int SENSE_IR_LEFT  = 0;
const int SENSE_IR_RIGHT = 1;

// defines for sonar sensor
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;

// define for servo pin
const int SERVO_PIN = 9;

// defines for IR sensors
const byte NBR_SENSORS = 2;  // this version only has left and right sensors
const byte IR_SENSOR[NBR_SENSORS] = {SENSE_IR_LEFT, SENSE_IR_RIGHT}; // analog pins for sensors

const int IR_REFLECT_THRESHOLD = 22;  // amount below ambient at which to trigger reflection
const int IR_EDGE_THRESHOLD = 22;     // amount above ambient at which to trigger edge

// defines for directions
const int DIR_LEFT   = 0;
const int DIR_RIGHT  = 1;
const int DIR_CENTER = 2;

const char* locationString[] = {"Left", "Right", "Center"}; // labels for debug
// see http://arduino.cc/en/Reference/String for more on character string arrays

// obstacles constants
const int OBST_NONE       = 0;  // no obstacle detected
const int OBST_LEFT_EDGE  = 1;  // left edge detected 
const int OBST_RIGHT_EDGE = 2;  // right edge detected
const int OBST_FRONT_EDGE = 3;  // edge detect at both left & right sensors
const int OBST_FRONT      = 4;  // obstacle in front
const int OBST_REAR       = 5;  // obstacle behind

const int LED_PIN = 13;

/// move states:
enum        {MOV_LEFT, MOV_RIGHT, MOV_FORWARD, MOV_BACK, MOV_ROTATE, MOV_STOP};
const char* states[] = {"Left", "Right", "Forward", "Back", "Rotate", "Stop"};

int moveState = MOV_STOP;
int prevMoveState = MOV_STOP;

// start characters for reading different control data
const char servoChar = 'S';
const char joystickXChar = 'X';
const char joystickYChar = 'Y';
const char autoFlagChar = 'M';

// serial reading buffer size
const int DATA_BUFFER_SIZE = 15;

// arrays to store control data
char servoData[DATA_BUFFER_SIZE];
char joystickXData[DATA_BUFFER_SIZE];
char joystickYData[DATA_BUFFER_SIZE];
char autoFlagData[DATA_BUFFER_SIZE];

// flags to indicate whether controls are being read
bool isReadingServo = false;
bool isReadingX = false;
bool isReadingY = false;
bool isReadingAutoFlag = false;

// variables to indicate current size of control data read
int servoDataSize = 0;
int xDataSize = 0;
int yDataSize = 0;
int autoFlagDataSize = 0;

// flags to indicate control data has been received
bool receivedServoData = false;
bool receivedJoystickData = false;
bool receivedAutoFlagData = false;

// flag to indicate whether bot is in explore mode
bool exploreMode = false;

#endif
