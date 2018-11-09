#include <math.h>  

//To keep track of all arrays and the number of values
const int NUM_SENSE_VALS = 2;
const int NUM_CTRL_VALS = 3;
const int SLACK = 50;

// Control Pins
// 0 = MTR_PN
// 1 = DIR_PIN_ONE
// 2 = DIR_PIN_TWO
const int CTRL_PINS[NUM_CTRL_VALS] = {13, 12, 11};

// Sensor pins
// 0 = LEFT_PHOTO
// 1 = RIGHT_PHOTO
const int SENSE_PINS[NUM_SENSE_VALS] = {A0, A1};

//Variables for motor state
bool states[NUM_CTRL_VALS] = {false, false, false};
float sensorValues[NUM_SENSE_VALS] = {0,0};

//Variables for motor control
bool reqStates[NUM_CTRL_VALS] = {false, false, false};

void setup() {
  for(int i = 0; i < NUM_CTRL_VALS-1; i++){
    pinMode(CTRL_PINS[i], OUTPUT);
  }

  for(int i = 0; i < NUM_SENSE_VALS-1; i++){
    pinMode(SENSE_PINS[i], OUTPUT);
  }

  for(int i = 0; i < NUM_CTRL_VALS-1; i++){
    digitalWrite(CTRL_PINS[i], states[i]);
  }
}

void loop() {
  senseData();

  calculateRequirements();
  // This is called at the end of the loop to react to input
  reactToData();
}

void calculateRequirements(){
    reqStates[0] = (sensorValues[0] == sensorValues[1] || sensorValues[0] > sensorValues[1] - SLACK || sensorValues[0] < sensorValues[1] + SLACK );
    reqStates[1] = (sensorValues[0] > sensorValues[1]);
    reqStates[2] = (sensorValues[0] < sensorValues[1]);
  //if(sensorValues[0] % sensorValues[1] != 0){
  //  if(sensorValues[0] > sensorValues[1]){
  //    reqStates = {true, true, false};
  //  }else{
  //    reqStates
  //  }
  //}else{
  //  reqStates = {false, false, false};
  //}
}

void senseData(){
  for(int i = 0; i < NUM_SENSE_VALS-1; i++){
    sensorValues[i] = analogRead(SENSE_PINS[i]);
  }
}

void reactToData(){
  for(int i = 0; i < NUM_CTRL_VALS-1; i++){
    if(states[i] != reqStates[i]){
      states[i] = reqStates[i];
      digitalWrite(CTRL_PINS[i], states[i]);
    }
  }
}
