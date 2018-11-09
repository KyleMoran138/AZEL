#include <math.h>  

//To keep track of all arrays and the number of values
const int NUM_SENSE_VALS = 2;
const int NUM_CTRL_VALS = 3;
const int SLACK = 5;

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
  Serial.begin(9600);
  Serial.println("Begin");
  for(int i = 0; i < NUM_CTRL_VALS; i++){
    pinMode(CTRL_PINS[i], OUTPUT);
  }

  for(int i = 0; i < NUM_SENSE_VALS; i++){
    pinMode(SENSE_PINS[i], OUTPUT);
  }

  for(int i = 0; i < NUM_CTRL_VALS; i++){
    digitalWrite(CTRL_PINS[i], states[i]);
  }
}

void loop() {
  senseData();

  calculateRequirements();
  // This is called at the end of the loop to react to input
  reactToData();
  delay(500);
}

void calculateRequirements(){
    float dist = sensorValues[0] - sensorValues[1];
    reqStates[0] = dist > SLACK || dist < -SLACK;
    reqStates[1] = dist > SLACK;
    reqStates[2] = dist < -SLACK;

    Serial.println(reqStates[0]);
    Serial.println(reqStates[1]);
    Serial.println(reqStates[2]);
    
}

void senseData(){
  for(int i = 0; i < NUM_SENSE_VALS; i++){
    sensorValues[i] = analogRead(SENSE_PINS[i]);
    Serial.println("Sensor " + String(i) + " Value: " + String(sensorValues[i]));
  }
}

void reactToData(){
  for(int i = 0; i < NUM_CTRL_VALS; i++){
    if(states[i] != reqStates[i]){
      states[i] = reqStates[i];
      digitalWrite(CTRL_PINS[i], states[i]);
    }
  }
}
