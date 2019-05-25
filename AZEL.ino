#include <math.h>
#include "Arduino.h"
#include "Sensor.h"
#include "PhotoResistor.h"
#include "SensorArray.h"
#include "Stepper.h"
//To keep track of all arrays and the number of values
const int NUM_SENSE_VALS = 3;
const int NUM_CTRL_VALS = 4;
const int SLACK = 5;

// Control Pins
// 0 =  A
// 1 = A|
// 2 = B
// 3 = B|
const int CTRL_PINS[NUM_CTRL_VALS] = {11, 9, 10, 8};

// Sensor pins
// 0 = LEFT_PHOTO
// 1 = RIGHT_PHOTO
const int SENSE_PINS[NUM_SENSE_VALS] = {A0, A1, A2};
const float SENSE_PINS_LOCATION[NUM_SENSE_VALS] = {.25, 0, .75};
bool isDed = false;

Sensor *all_sensors[NUM_SENSE_VALS];
SensorArray *senArr;
Stepper  *motorOne;

//Variables for motor control and current states
bool reqStates[NUM_CTRL_VALS] = {false, false, false};
bool states[NUM_CTRL_VALS] = {false, false, false};

#define SERIAL_OUTPUT

void setup() {
  #ifdef SERIAL_OUTPUT
    Serial.begin(9600);
    delay(500);
    Serial.println("Begin");
  #endif

  for(int i = 0; i < NUM_CTRL_VALS; i++){
    pinMode(CTRL_PINS[i], OUTPUT);
  }

  for(int i = 0; i < NUM_SENSE_VALS; i++){
    pinMode(SENSE_PINS[i], INPUT);
  }

  for(int i = 0; i < NUM_CTRL_VALS; i++){
    digitalWrite(CTRL_PINS[i], states[i]);
  }

  // Give the board some time to set up the ports
  delay(1000);

  for(int i = 0; i < NUM_SENSE_VALS; i++){
    all_sensors[i] = new PhotoResistor(SENSE_PINS[i], SENSE_PINS_LOCATION[i]);
  }

  senArr = new SensorArray(all_sensors, NUM_SENSE_VALS);
  motorOne = new Stepper();
}

void loop() {
  //Serial.println("loop");
  if(!isDed){
    isDed = true;
    senArr->readAllSensorValues();
    senArr->calculateAngle();
    int dir = senArr->getSensorTurnDirection(1, 1024);
    Serial.print("Dir to turn: ");
    Serial.println(dir);
    if(dir != 0){
      Serial.println(senArr->getDistanceToRotateBy(1, 1024, dir));
      // Serial.print("Degrees to turn: ");
      // Serial.println(4);
      motorOne->DoStep(dir==1, 10);
    }

  }
  delay(1000);
}
